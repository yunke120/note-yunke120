

## 汇编LED原理分析

### 1. 为什么要学习Cotex-A汇编

- 需要用汇编初始化一些SOC外设
- 使用汇编初始化DDR，I.MX6U不需要
- 设置sp指针，一般指向DDR，设置好C语言运行环境

### 2. I.MX6ULL IO 初始化流程

1. **使能时钟**。CCGR0~CCGR6这7个寄存器控制着I.MX6ULL所有的时钟使能。为了简单，设置CCGR0-CCGR6这7个寄存器全部为0XFFFFFFFF，相当于使能所有外设时钟。

2. **IO复用**。设置  IOMUXC_SW_ $\color{#FF0000}{MUX}$ _CTL_PAD_GPIO1_IO03   的 bit3~0 设置为 0101=5，将其复用为GPIO

   > 0101 ALT5 — Select mux mode: ALT5 mux port: GPIO1_IO03 of instance: gpio1

3. **设置电气属性**。设置   IOMUXC_SW_ $\color{#FF0000}{PAD}$ _CTL_PAD_GPIO1_IO03  ，包括压摆率、速度、驱动能力、开漏、上下拉等。
4. **配置GPIO功能**。设置输入输出。设置 GPIO3_GDIR 的bit3为1，即设置为输出模式；设置 GPIO3_DR 的bit3为1，即设置为输出高电平，0为输出低电平；

### 3. 编写驱动

​	点灯led汇编程序

```

.global _start

_start:
    /* enable all clock */
    ldr r0, = 0x020c4068 @ CCGR0
    ldr r1, = 0xffffffff  @ data -> CCGR0
    str r1, [r0]          @ 0xffffffff -> CCGR0

    ldr r0, = 0x020c406c
    str r1, [r0]

    ldr r0, = 0x020c4070
    str r1, [r0]

    ldr r0, = 0x020c4074
    str r1, [r0]

    ldr r0, = 0x020c4078
    str r1, [r0]

    ldr r0, = 0x020c407c
    str r1, [r0]

    ldr r0, = 0x020c4080 @ CCGR6
    str r1, [r0]

    /* config IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO03 mux gpio, bit3~0 = 0101 */
    ldr r0, =0x020e0068
    ldr r1, = 0x5
    str r1, [r0]

    /* config IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO03 
     * 20E_02F4 
     * bit0: 0 low
     * bit5-3: drive strength field 110 R0/6
     * bit7-6:10 100MHZ
     * bit11: 0 close open drain
     * bit12: 1 enable pull
     * bit13: 0 keeper
     * bit15-14 00 100K pull down
     * bit16: 0 
     */
    ldr r0, = 0x020e02f4
    ldr r1, = 0x10b0
    str r1, [r0]

     /* set gpio  
      * 209_C004  GPIO1_GDIR
      * bit3 = 1 output
      */
    ldr r0, = 0x0209c004
    ldr r1, = 0x8
    str r1, [r0]

    /* open led 
     * GPIO1_DR 209c000
     */
    ldr r0, = 0x0209c000
    ldr r1, = 0x0
    str r1, [r0]

loop:
    b loop
```

编译程序：

1. 将`.c`、`.s`文件编译为`.o`文件

   ```asp
   arm-linux-gnueabihf-gcc -g -c xxx.s -o xxx.o
   ```

2. 将所有的`.o`文件链接为`.elf`格式的可执行文件

   > 链接就是将所有的`.o`文件链接在一起，并且链接到指定的地方。本实验链接的时候要指定起始地址。链接起始地址就是代码运行的起始地址
   >
   > 对于6ULL来说，链接起始地址应该指向RAM地址。RAM分为内部RAM和外部RAM，也就是DDR.内部RAM的地址范围0X900000~0X91FFFF。也可以放到外部RAM

   ```
   arm-linux-gnueabihf-ld -Ttext 0x87800000 xxx.o -o xxx.elf
   ```

3. 将`.elf`文件转为`.bin`文件

   ```
   arm-linux-gnueabihf-objcopy -O binary -g -S xxx.elf xxx.bin
   ```

4. 将`.elf`文件转为汇编，反汇编

   ```
   arm-linux-gnueabihf-objdump -D xxx.elf > xxx.dis
   ```

5. 烧写`.bin`文件

   > STM32烧写到内部flash
   >
   > 6ULL支持SD卡、EMMC、NAND、norflash、SPI Flash等等启动。裸机例程选择烧写到SD卡中

   在Ubuntu中将`.bin`烧写到SD卡中。

   > 烧写不是将bin文件拷贝到SD卡中，而是将bin文件烧写到SD卡绝对地址上，对于I.MX而言，不能直接烧写bin文件，比如需要先在bin文件前面添加头部。完成这个工作，需要使用正点原子提供的 imxdownload 软件

   ```
   ./imxdownload xxx.bin /dev/sdb
   ```

   