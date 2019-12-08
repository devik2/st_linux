#!/bin/bash

make -j2 ARCH=arm uImage LOADADDR=0xc1000000
cp arch/arm/boot/uImage /tmp
make ARCH=arm dtbs
#mkimage -A arm -n dtb -a 0xc1f00000 -d arch/arm/boot/dts/stm32mp157a-portk.dtb /tmp/udtb
#mkimage -A arm -n dtb -a 0xc1f00000 -d arch/arm/boot/dts/stm32mp157a-som-rza.dtb /tmp/udtb
mkimage -A arm -n dtb -a 0xc1f00000 -d arch/arm/boot/dts/stm32mp157a-fpga-tst1.dtb /tmp/udtb
