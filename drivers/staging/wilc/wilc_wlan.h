/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (c) 2012 - 2018 Microchip Technology Inc., and its subsidiaries.
 * All rights reserved.
 */

#ifndef WILC_WLAN_H
#define WILC_WLAN_H

#include <linux/types.h>
#include <linux/version.h>

static inline bool is_wilc1000(u32 id)
{
	return (id & 0xfffff000) == 0x100000;
}

static inline bool is_wilc3000(u32 id)
{
	return (id & 0xfffff000) == 0x300000;
}

/********************************************
 *
 *      Mac eth header length
 *
 ********************************************/
#define MAX_MAC_HDR_LEN			26 /* QOS_MAC_HDR_LEN */
#define SUB_MSDU_HEADER_LENGTH		14
#define SNAP_HDR_LEN			8
#define ETHERNET_HDR_LEN		14
#define WORD_ALIGNMENT_PAD		0

#define ETH_ETHERNET_HDR_OFFSET		(MAX_MAC_HDR_LEN + \
					 SUB_MSDU_HEADER_LENGTH + \
					 SNAP_HDR_LEN - \
					 ETHERNET_HDR_LEN + \
					 WORD_ALIGNMENT_PAD)

#define HOST_HDR_OFFSET			4
#define ETHERNET_HDR_LEN		14
#define IP_HDR_LEN			20
#define IP_HDR_OFFSET			ETHERNET_HDR_LEN
#define UDP_HDR_OFFSET			(IP_HDR_LEN + IP_HDR_OFFSET)
#define UDP_HDR_LEN			8
#define UDP_DATA_OFFSET			(UDP_HDR_OFFSET + UDP_HDR_LEN)
#define ETH_CONFIG_PKT_HDR_LEN		UDP_DATA_OFFSET

#define ETH_CONFIG_PKT_HDR_OFFSET	(ETH_ETHERNET_HDR_OFFSET + \
					 ETH_CONFIG_PKT_HDR_LEN)
#define PKT_STATUS_NEW          0
#define PKT_STATUS_BUFFERED     1

/********************************************
 *
 *      Register Defines
 *
 ********************************************/
#define WILC_PERIPH_REG_BASE		0x1000
#define WILC_CHIPID			WILC_PERIPH_REG_BASE
#define WILC_GLB_RESET_0		(WILC_PERIPH_REG_BASE + 0x400)
#define WILC_PIN_MUX_0			(WILC_PERIPH_REG_BASE + 0x408)
#define WILC_HOST_TX_CTRL		(WILC_PERIPH_REG_BASE + 0x6c)
#define WILC_HOST_RX_CTRL_0		(WILC_PERIPH_REG_BASE + 0x70)
#define WILC_HOST_RX_CTRL_1		(WILC_PERIPH_REG_BASE + 0x74)
#define WILC_HOST_VMM_CTL		(WILC_PERIPH_REG_BASE + 0x78)
#define WILC_HOST_RX_CTRL		(WILC_PERIPH_REG_BASE + 0x80)
#define WILC_HOST_RX_EXTRA_SIZE		(WILC_PERIPH_REG_BASE + 0x84)
#define WILC_HOST_TX_CTRL_1		(WILC_PERIPH_REG_BASE + 0x88)
#define WILC_INTERRUPT_CORTUS_0		(WILC_PERIPH_REG_BASE + 0xa8)
#define WILC_MISC			(WILC_PERIPH_REG_BASE + 0x428)
#define WILC_INTR_REG_BASE		(WILC_PERIPH_REG_BASE + 0xa00)
#define WILC_INTR_ENABLE		WILC_INTR_REG_BASE
#define WILC_INTR2_ENABLE		(WILC_INTR_REG_BASE + 4)

#define WILC_INTR_POLARITY		(WILC_INTR_REG_BASE + 0x10)
#define WILC_INTR_TYPE			(WILC_INTR_REG_BASE + 0x20)
#define WILC_INTR_CLEAR			(WILC_INTR_REG_BASE + 0x30)
#define WILC_INTR_STATUS		(WILC_INTR_REG_BASE + 0x40)

#define WILC_VMM_TBL_SIZE		64
#define WILC_VMM_TX_TBL_BASE		0x150400
#define WILC_VMM_RX_TBL_BASE		0x150500

#define WILC_VMM_BASE			0x150000
#define WILC_VMM_CORE_CTL		WILC_VMM_BASE
#define WILC_VMM_TBL_CTL		(WILC_VMM_BASE + 0x4)
#define WILC_VMM_TBL_ENTRY		(WILC_VMM_BASE + 0x8)
#define WILC_VMM_TBL0_SIZE		(WILC_VMM_BASE + 0xc)
#define WILC_VMM_TO_HOST_SIZE		(WILC_VMM_BASE + 0x10)
#define WILC_VMM_CORE_CFG		(WILC_VMM_BASE + 0x14)
#define WILC_VMM_TBL_ACTIVE		(WILC_VMM_BASE + 040)
#define WILC_VMM_TBL_STATUS		(WILC_VMM_BASE + 0x44)

#define WILC_SPI_REG_BASE		0xe800
#define WILC_SPI_CTL			WILC_SPI_REG_BASE
#define WILC_SPI_MASTER_DMA_ADDR	(WILC_SPI_REG_BASE + 0x4)
#define WILC_SPI_MASTER_DMA_COUNT	(WILC_SPI_REG_BASE + 0x8)
#define WILC_SPI_SLAVE_DMA_ADDR		(WILC_SPI_REG_BASE + 0xc)
#define WILC_SPI_SLAVE_DMA_COUNT	(WILC_SPI_REG_BASE + 0x10)
#define WILC_SPI_TX_MODE		(WILC_SPI_REG_BASE + 0x20)
#define WILC_SPI_PROTOCOL_CONFIG	(WILC_SPI_REG_BASE + 0x24)
#define WILC_SPI_INTR_CTL		(WILC_SPI_REG_BASE + 0x2c)

#define WILC_SPI_PROTOCOL_OFFSET	(WILC_SPI_PROTOCOL_CONFIG - \
					 WILC_SPI_REG_BASE)

#define WILC_AHB_DATA_MEM_BASE		0x30000
#define WILC_AHB_SHARE_MEM_BASE		0xd0000

#define VMM_TBL_RX_SHADOW_BASE		WILC_AHB_SHARE_MEM_BASE
#define VMM_TBL_RX_SHADOW_SIZE		256

#define WILC_FW_HOST_COMM		0x13c0
#define WILC_GP_REG_0			0x149c
#define WILC_GP_REG_1			0x14a0

#define WILC_COEXIST_CTL		0x161E00
#define GLOBAL_MODE_CONTROL		0x1614
#define PWR_SEQ_MISC_CTRL		0x3008
#define COE_AUTO_PS_ON_NULL_PKT		0x160468
#define COE_AUTO_PS_OFF_NULL_PKT	0x16046C
#define CCA_CTL_2 (0x160EF4)
#define CCA_CTL_7 (0x160F08)

#define WILC_HAVE_SDIO_IRQ_GPIO		BIT(0)
#define WILC_HAVE_SLEEP_CLK_SRC_RTC	BIT(2)
#define WILC_HAVE_SLEEP_CLK_SRC_XO	BIT(3)

/********************************************
 *
 *      Wlan Defines
 *
 ********************************************/
#define WILC_CFG_PKT		1
#define WILC_NET_PKT		0
#define WILC_MGMT_PKT		2

#define WILC_CFG_SET		1
#define WILC_CFG_QUERY		0

#define WILC_CFG_RSP		1
#define WILC_CFG_RSP_STATUS	2
#define WILC_CFG_RSP_SCAN	3
#define WILC_ABORT_REQ_BIT		BIT(31)

#define WILC_RX_BUFF_SIZE	(96 * 1024)
#define WILC_TX_BUFF_SIZE	(64 * 1024)

#define MODALIAS		"WILC_SPI"
#define GPIO_NUM		0x5B
#define GPIO_NUM_CHIP_EN	94
#define GPIO_NUM_RESET		60

#define NQUEUES			4
#define VO_AC_COUNT_POS		25
#define VO_AC_ACM_STAT_POS	24
#define VI_AC_COUNT_POS		17
#define VI_AC_ACM_STAT_POS	16
#define BE_AC_COUNT_POS		9
#define BE_AC_ACM_STAT_POS	8
#define BK_AC_COUNT_POS		2
#define BK_AC_ACM_STAT_POS	1
#define AC_BUFFER_SIZE		1000
/*******************************************/
/*        E0 and later Interrupt flags.    */
/*******************************************/
/*******************************************/
/*        E0 and later Interrupt flags.    */
/*           IRQ Status word               */
/* 15:0 = DMA count in words.              */
/* 16: INT0 flag                           */
/* 17: INT1 flag                           */
/* 18: INT2 flag                           */
/* 19: INT3 flag                           */
/* 20: INT4 flag                           */
/* 21: INT5 flag                           */
/*******************************************/
#define IRG_FLAGS_OFFSET	16
#define IRQ_DMA_WD_CNT_MASK	((1ul << IRG_FLAGS_OFFSET) - 1)
#define INT_0			BIT(IRG_FLAGS_OFFSET)
#define INT_1			BIT(IRG_FLAGS_OFFSET + 1)
#define INT_2			BIT(IRG_FLAGS_OFFSET + 2)
#define INT_3			BIT(IRG_FLAGS_OFFSET + 3)
#define INT_4			BIT(IRG_FLAGS_OFFSET + 4)
#define MAX_NUM_INT		5

/*******************************************/
/*        E0 and later Interrupt flags.    */
/*           IRQ Clear word                */
/* 0: Clear INT0                           */
/* 1: Clear INT1                           */
/* 2: Clear INT2                           */
/* 3: Clear INT3                           */
/* 4: Clear INT4                           */
/* 5: Clear INT5                           */
/* 6: Select VMM table 1                   */
/* 7: Select VMM table 2                   */
/* 8: Enable VMM                           */
/*******************************************/
#define CLR_INT0		BIT(0)
#define CLR_INT1		BIT(1)
#define CLR_INT2		BIT(2)
#define CLR_INT3		BIT(3)
#define CLR_INT4		BIT(4)
#define CLR_INT5		BIT(5)
#define SEL_VMM_TBL0		BIT(6)
#define SEL_VMM_TBL1		BIT(7)
#define EN_VMM			BIT(8)

#define DATA_INT_EXT		INT_0
#define ALL_INT_EXT		(DATA_INT_EXT)
#define NUM_INT_EXT		1

#define DATA_INT_CLR		CLR_INT0

#define ENABLE_RX_VMM		(SEL_VMM_TBL1 | EN_VMM)
#define ENABLE_TX_VMM		(SEL_VMM_TBL0 | EN_VMM)
/*time for expiring the completion of cfg packets*/
#define WILC_CFG_PKTS_TIMEOUT	msecs_to_jiffies(3000)

#define IS_MANAGMEMENT		0x100
#define IS_MANAGMEMENT_CALLBACK	0x080
#define IS_MGMT_STATUS_SUCCES	0x040
#define IS_MON_PKT		0x020

/********************************************
 *
 *      Tx/Rx Queue Structure
 *
 ********************************************/

enum ip_pkt_priority {
	AC_VO_Q = 0,
	AC_VI_Q = 1,
	AC_BE_Q = 2,
	AC_BK_Q = 3
};

struct txq_entry_t {
	struct list_head list;
	int type;
	u8 q_num;
	int ack_idx;
	u8 *buffer;
	int buffer_size;
	void *priv;
	int status;
	struct wilc_vif *vif;
	void (*tx_complete_func)(void *priv, int status);
};

struct txq_handle {
	struct txq_entry_t txq_head;
	u16 count;
	u8 acm;
};

struct rxq_entry_t {
	struct list_head list;
	u8 *buffer;
	int buffer_size;
};

enum wilc_chip_type {
	WILC_1000,
	WILC_3000,
};

/********************************************
 *
 *      Host IF Structure
 *
 ********************************************/
struct wilc;
struct wilc_hif_func {
	int (*hif_init)(struct wilc *wilc, bool resume);
	int (*hif_deinit)(struct wilc *wilc);
	int (*hif_read_reg)(struct wilc *wilc, u32 addr, u32 *data);
	int (*hif_write_reg)(struct wilc *wilc, u32 addr, u32 data);
	int (*hif_block_rx)(struct wilc *wilc, u32 addr, u8 *buf, u32 size);
	int (*hif_block_tx)(struct wilc *wilc, u32 addr, u8 *buf, u32 size);
	int (*hif_read_int)(struct wilc *wilc, u32 *int_status);
	int (*hif_clear_int_ext)(struct wilc *wilc, u32 val);
	int (*hif_read_size)(struct wilc *wilc, u32 *size);
	int (*hif_block_tx_ext)(struct wilc *wilc, u32 addr, u8 *buf, u32 size);
	int (*hif_block_rx_ext)(struct wilc *wilc, u32 addr, u8 *buf, u32 size);
	int (*hif_sync_ext)(struct wilc *wilc, int nint);
	int (*enable_interrupt)(struct wilc *nic);
	void (*disable_interrupt)(struct wilc *nic);
	int (*hif_reset)(struct wilc *wilc);
	bool (*hif_is_init)(struct wilc *wilc);
};

#define WILC_MAX_CFG_FRAME_SIZE		1468

struct tx_complete_data {
	int size;
	void *buff;
	struct sk_buff *skb;
	struct wilc_vif *vif;
};

struct wilc_cfg_cmd_hdr {
	u8 cmd_type;
	u8 seq_no;
	__le16 total_len;
	__le32 driver_handler;
};

struct wilc_cfg_frame {
	struct wilc_cfg_cmd_hdr hdr;
	u8 frame[WILC_MAX_CFG_FRAME_SIZE];
};

struct wilc_cfg_rsp {
	u8 type;
	u8 seq_no;
};

struct wilc;
struct wilc_vif;

int wilc_wlan_firmware_download(struct wilc *wilc, const u8 *buffer,
				u32 buffer_size);
int wilc_wlan_start(struct wilc *wilc);
int wilc_wlan_stop(struct wilc *wilc, struct wilc_vif *vif);
int txq_add_net_pkt(struct net_device *dev, void *priv, u8 *buffer,
			      u32 buffer_size,
			      void (*tx_complete_fn)(void *, int));
int wilc_wlan_handle_txq(struct wilc *wilc, u32 *txq_count);
void wilc_handle_isr(struct wilc *wilc);
void wilc_wlan_cleanup(struct net_device *dev);
int cfg_set(struct wilc_vif *vif, int start, u16 wid, u8 *buffer,
		      u32 buffer_size, int commit, u32 drv_handler);
int cfg_get(struct wilc_vif *vif, int start, u16 wid, int commit,
		      u32 drv_handler);
int txq_add_mgmt_pkt(struct net_device *dev, void *priv, u8 *buffer,
			       u32 buffer_size,
			       void (*tx_complete_fn)(void *, int));

void wilc_enable_tcp_ack_filter(struct wilc_vif *vif, bool value);
netdev_tx_t wilc_mac_xmit(struct sk_buff *skb, struct net_device *dev);

bool wilc_wfi_p2p_rx(struct wilc_vif *vif, u8 *buff, u32 size);
void host_wakeup_notify(struct wilc *wilc, int source);
void host_sleep_notify(struct wilc *wilc, int source);
void chip_allow_sleep(struct wilc *wilc, int source);
void chip_wakeup(struct wilc *wilc, int source);
int wilc_send_config_pkt(struct wilc_vif *vif, u8 mode, struct wid *wids,
			 u32 count);
void wilc_wlan_power_on_sequence(struct wilc *wilc);
void wilc_wlan_power_off_sequence(struct wilc *wilc);

void wilc_bt_init(struct wilc *wilc);
void wilc_bt_deinit(void);
#if KERNEL_VERSION(4, 15, 0) <= LINUX_VERSION_CODE
void eap_buff_timeout(struct timer_list *t);
#else
void eap_buff_timeout(unsigned long user);
#endif
void acquire_bus(struct wilc *wilc, enum bus_acquire acquire, int source);
void release_bus(struct wilc *wilc, enum bus_release release, int source);
int wilc_wlan_init(struct net_device *dev);
u32 wilc_get_chipid(struct wilc *wilc, bool update);
void wilc_wfi_handle_monitor_rx(struct wilc *wilc, u8 *buff, u32 size);
#endif
