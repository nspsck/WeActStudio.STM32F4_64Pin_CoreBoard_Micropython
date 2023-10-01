# WeActStudio.STM32F4_64Pin_CoreBoard_Micropython

This port gives you a py-board-like experience using the STM32F446RE, STM32F412RE and STM32F405RG core boards created by WeAct Studio.

The pre-built firmware could be found in each target's folder.

The pins/features-configurations are final, changes will only be done when forced by Micropython updates.

There is a `NO_CONFLICT` version available, in which all available peripherals can work at the same time, except for `CAN1` and `I2C1`. However, since they share the same pins, they won't be running togather, hence no conflicts :D (problem solved!). Also the  pins definition below no longer holds for the `NO_CONFLICT` version.

## Pins definition

Things that in `()` are not available in the pre-built firmware but they have their definitions in the `mpconfigboard.h` file. These are only my choices, you may use any other pins, which were sated in the comment as `Valid`. Default `USART-REPL` is on `USART6`.

### Common

| USART  | USART1 | USART2 | USART6 |
| ------ | ------ | ------ | ------ |
| TX     | A9     | A2     | C6     |
| RX     | A10    | A3     | C7     |

| I2C  | I2C1 |
| ---- | ---- |
| SCL  | B8   |
| SDA  | B9   |

| SPI    | SPI1   | SPI2   | SPI3   |
| ------ | ------ | ------ | ------ |
| NSS    | A4     | B12    | A15    |
| SCK    | A5     | B13    | B3     |
| MISO   | A6     | B14    | B4     |
| MOSI   | A7     | B15    | B5     |

| CAN  | CAN1 | CAN2 |
| ---- | ---- | ---- |
| TX   | B9   | B6   |
| RX   | B8   | B5   |

| LED  | KEY | USB_DM | USB_DP |
| ---- | --- | ------ | ------ |
| B2   | C13 | PA11   | PA12   |

| SD_CK  | SD_CMD | SD_D0 | SD_D1 | SD_D2 | SD_D3 | SD_Detect |
| ------ | ------ | ----- | ----- | ----- | ----- | --------- |
| C12    | D2     | C8    | C9    | C10   | C11   | A8        |

## Storage modification

If changing the flash layout is at your interest, you can modify the following section the `.ld` file. 
```ld
MEMORY
{
    FLASH (rx)      : ORIGIN = 0x08000000, LENGTH = 512K /* entire flash */
    FLASH_ISR (rx)  : ORIGIN = 0x08000000, LENGTH = 16K /* sector 0 */
    /* This is your space for storing Code. */
    FLASH_FS (rx)   : ORIGIN = 0x08004000, LENGTH = 176K /* sectors 1,2,3,4,5: 16k+16k+16k+64K+64K(of 128K)=176K */
    /* This is where the firmware is stored. */
    FLASH_TEXT (rx) : ORIGIN = 0x08030000, LENGTH = 320K /* sectors 5, 6, 7: 64K(of 128K)+128K+128K=320K */
    RAM (xrw)       : ORIGIN = 0x20000000, LENGTH = 112K
    FS_CACHE (xrw)  : ORIGIN = 0x2001c000, LENGTH = 16K
}
```
Please make sure you modify the `TEXT0_ADDR` and `TEXT1_ADDR` in `mpconfigboard.mk` as well if you intend to use `.bin` files. Tho, you can also just delete these 2 lines and just use the `.hex` file. Please do not change RAM settings unless you know what you are doing. Also, the `STM32F446` is not like the other boards, it seems like it requires the `FLASH_TEXT` to start at a section's beginning. Please keep that in mind.

## How to build

First of all, you have to have a linux enviroment and get the compilers.
```shell
sudo apt-get -y install gcc-arm-none-eabi build-essential
```
After that, open the terminal and clone the official Micropython repo:
```shell
git clone https://github.com/micropython/micropython.git
cd micropython
git submodule update --init --recursive
cd mpy-cross
make -j
```
Copy `WEACTF4xxRx' to the `micropython/ports/stm32/boards` folder. To build the firmware, make sure you are in the `micropython/ports/stm32` folder, and type the following:
```shell
make -j LTO=1 BOARD=WEACTF4xxRx # Please replace 'x' with your targeted MCU.
```
There are 4 possible variants for the both of the boards: `DP`, `THREAD`, `DP_THREAD` and `NETWORK`. The `NETWORK` variant should not be used as it requires other components that has to be purchased separately.
```shell
# replace VARIANTS with DP, THREAD or DP_THREAD
# DP: Use double precision for floats, each float number takes twice as much memory.
# THREAD: Enables Thread. This is an experiemental feature
# DP_THREAD: Enables Thread and use double precision.
make -j LTO=1 BOARD=WEACTF4xxRx BOARD_VARIANT=VARIANTS
```
