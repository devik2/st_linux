// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (C) STMicroelectronics 2018 - All Rights Reserved
 * Author: Gabriel Fernandez <gabriel.fernandez@st.com> for STMicroelectronics.
 */

#include <linux/arm-smccc.h>
#include <linux/device.h>
#include <linux/err.h>
#include <linux/io.h>
#include <linux/of.h>
#include <linux/platform_device.h>
#include <linux/reset-controller.h>
#include <linux/reboot.h>
#include <linux/delay.h>

#define CLR_OFFSET 0x4

#define RCC_MP_GRSTCSETR 0x404
#define STM32_RCC_TZCR 0x0
#define CLR_OFFSET 0x4

#define STM32MP1_SVC_RCC 0x82001000

#define SMT32_SPI6_R 3136
#define STM32_AXIM_R 3216
#define STM32_MCU_R 8225

struct stm32_reset_data {
	struct reset_controller_dev	rcdev;
	void __iomem			*membase;
	struct notifier_block reset_nb;
};

static int soc_secured;

static int is_stm32_id_secured(unsigned long id)
{
	if (id >= SMT32_SPI6_R && id <= STM32_AXIM_R)
		return 1;

	if (id == STM32_MCU_R)
		return 1;

	return 0;
}

static int reset_stm32_secure_update(struct reset_controller_dev *rcdev,
				     unsigned long id, bool assert)
{
	struct arm_smccc_res res;
	int bank = id / BITS_PER_LONG;
	int offset = id % BITS_PER_LONG;

	if (assert)
		arm_smccc_smc(STM32MP1_SVC_RCC, 0x1, (bank * 4),
			      BIT(offset), 0, 0, 0, 0, &res);
	else
		arm_smccc_smc(STM32MP1_SVC_RCC, 0x1, (bank * 4) + CLR_OFFSET,
			      BIT(offset), 0, 0, 0, 0, &res);

	return 0;
}

static inline struct stm32_reset_data *
to_stm32_reset_data(struct reset_controller_dev *rcdev)
{
	return container_of(rcdev, struct stm32_reset_data, rcdev);
}

static int stm32_reset_update(struct reset_controller_dev *rcdev,
			      unsigned long id, bool assert)
{
	struct stm32_reset_data *data = to_stm32_reset_data(rcdev);
	int reg_width = sizeof(u32);
	int bank = id / (reg_width * BITS_PER_BYTE);
	int offset = id % (reg_width * BITS_PER_BYTE);
	void __iomem *addr;

	addr = data->membase + (bank * reg_width);
	if (!assert)
		addr += CLR_OFFSET;

	writel(BIT(offset), addr);

	return 0;
}

static int stm32_reset_assert(struct reset_controller_dev *rcdev,
			      unsigned long id)
{
	if (soc_secured && is_stm32_id_secured(id))
		return reset_stm32_secure_update(rcdev, id, true);

	return stm32_reset_update(rcdev, id, true);
}

static int stm32_reset_deassert(struct reset_controller_dev *rcdev,
				unsigned long id)
{
	if (soc_secured && is_stm32_id_secured(id))
		return reset_stm32_secure_update(rcdev, id, false);

	return stm32_reset_update(rcdev, id, false);
}

static int stm32_reset_status(struct reset_controller_dev *rcdev,
			      unsigned long id)
{
	struct stm32_reset_data *data = to_stm32_reset_data(rcdev);
	int reg_width = sizeof(u32);
	int bank = id / (reg_width * BITS_PER_BYTE);
	int offset = id % (reg_width * BITS_PER_BYTE);
	u32 reg;

	reg = readl(data->membase + (bank * reg_width));

	return !!(reg & BIT(offset));
}

static const struct reset_control_ops stm32_reset_ops = {
	.assert		= stm32_reset_assert,
	.deassert	= stm32_reset_deassert,
	.status		= stm32_reset_status,
};

static const struct of_device_id stm32_reset_dt_ids[] = {
	{ .compatible = "st,stm32mp1-rcc"},
	{ /* sentinel */ },
};

static int stm32_reset_by_rcc(struct notifier_block *this,
			    unsigned long mode, void *cmd)
{
	struct stm32_reset_data *rdata = container_of(this,
					struct stm32_reset_data, reset_nb);
	if (!soc_secured) {
		/* nonsecure system reboot, in secure mode, reboot is
		   expected to go thru PSCI */
		pr_info("Reseting by RCC MPSYSRST\n");
		udelay(2000);
		*(u32*)(rdata->membase + RCC_MP_GRSTCSETR) = 1; 
	}
	return NOTIFY_DONE;
}

static int stm32_reset_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct stm32_reset_data *data;
	void __iomem *membase;
	struct resource *res;

	data = devm_kzalloc(dev, sizeof(*data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	data->reset_nb.notifier_call = stm32_reset_by_rcc;
	data->reset_nb.priority = 120;
	register_restart_handler(&data->reset_nb);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	membase = devm_ioremap_resource(dev, res);
	if (IS_ERR(membase))
		return PTR_ERR(membase);

	data->membase = membase;
	data->rcdev.owner = THIS_MODULE;
	data->rcdev.nr_resets = resource_size(res) * BITS_PER_BYTE;
	data->rcdev.ops = &stm32_reset_ops;
	data->rcdev.of_node = dev->of_node;

	soc_secured = readl(membase + STM32_RCC_TZCR) & 0x1;

	return devm_reset_controller_register(dev, &data->rcdev);
}

static struct platform_driver stm32_reset_driver = {
	.probe	= stm32_reset_probe,
	.driver = {
		.name		= "stm32mp1-reset",
		.of_match_table	= stm32_reset_dt_ids,
	},
};

builtin_platform_driver(stm32_reset_driver);
