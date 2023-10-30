# WeActStudio.STM32F4_64Pin_CoreBoard_Micropython

This port gives you a py-board-like experience using the STM32F446RE, STM32F412RE and STM32F405RG core boards created by WeAct Studio.

The pre-built firmware could be found in each target's folder.

The pins/features-configurations are final, changes will only be done when forced by Micropython updates.

## Pins definition

Things that in `()` are not available in the pre-built firmware but they have their definitions in the `mpconfigboard.h` file. These are only my choices, you may use any other pins, which were sated in the comment as `Valid`. Default `USART-REPL` is on `USART1`.

### Common

| USART  | USART1 | USART2 | USART6 |
| ------ | ------ | ------ | ------ |
| TX     | A9     | A2     | C6     |
| RX     | A10    | A3     | C7     |

| I2C  | I2C1 |
| ---- | ---- |
| SCL  | B8   |
| SDA  | B9   |

| SPI    | SPI1   | SPI2   |
| ------ | ------ | ------ |
| NSS    | A4     | B12    |
| SCK    | A5     | B13    |
| MISO   | A6     | B14    |
| MOSI   | A7     | B15    |

| CAN  | CAN1 |
| ---- | ---- |
| TX   | B9   |
| RX   | B8   |

| LED  | KEY | USB_DM | USB_DP |
| ---- | --- | ------ | ------ |
| B2   | C13 | PA11   | PA12   |

| SD_CK  | SD_CMD | SD_D0 | SD_D1 | SD_D2 | SD_D3 | SD_Detect |
| ------ | ------ | ----- | ----- | ----- | ----- | --------- |
| C12    | D2     | C8    | C9    | C10   | C11   | A8        |

### STM32F405RG
| USART  | UART4 |
| ------ | ----- |
| TX     | A1    |
| RX     | A0    |

| I2C  | I2C2  |
| ---- | ----- |
| SCL  | B10   |
| SDA  | B11   |

| SPI    | SPI3   |
| ------ | ------ |
| NSS    | A15    |
| SCK    | B3     |
| MISO   | B4     |
| MOSI   | B5     |

### STM32F446RE
| USART  | UART4 |
| ------ | ----- |
| TX     | A1    |
| RX     | A0    |

| I2C  | I2C2 |
| ---- | ---- |
| SCL  | B10  |
| SDA  | B3   |

### STM32F412RE
| I2C  | I2C2 |
| ---- | ---- |
| SCL  | B10  |
| SDA  | B3   |

| CAN  | CAN2 |
| ---- | ---- |
| TX   | B6   |
| RX   | B5   |

## Storage modification

If you wish to make changes to the flash layouts, please visit [https://github.com/nspsck/STM32F411CEU6_BlackPill_Micropython#storage-modification](https://github.com/nspsck/STM32F411CEU6_BlackPill_Micropython#storage-modification) for a short guide. Tho, this should not be necessary, since all the boards comes with SDCard slot.

## Lfs2 Support

`Lfs2` is a little fail-safe filesystem designed for microcontrollers that supports dynamic wear leveling, which is quiet useful when you are using the internal flash to log datas, since `FAT` does not have a wear leveling implementation and you will be wearing off your 10K cycles quiet fast.

To format the filesystem to `Lfs2` you can simply excute the following code:

```python
import os, pyb
os.umount('/flash')
os.VfsLfs2.mkfs(pyb.Flash(start=0))
os.mount(pyb.Flash(start=0), '/flash')
os.chdir('/flash')
```

To avoid the annoying Windows formatation message, add the following to `boot.py`:

```python
import pyb
pyb.usb_mode('VCP') # This will change the COM-number on Windows.
```

To go back to `FAT`:

```python
import os, pyb
os.umount('/flash')
os.VfsFat.mkfs(pyb.Flash(start=0))
os.mount(pyb.Flash(start=0), '/flash')
os.chdir('/flash')
```

To use a hybrid mode:
```python
import os, pyb
os.umount('/flash')
p1 = pyb.Flash(start=0, len=256*1024) # You have to caculate the length by your self.
p2 = pyb.Flash(start=256*1024) # You have to caculate the length by your self.
os.VfsFat.mkfs(p1)
os.VfsLfs2.mkfs(p2)
os.mount(p1, '/flash')
os.mount(p2, '/data')
os.chdir('/flash')
```

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
## How to Flash

### Flashing the firmware
You can flash the firmware by following the official guide on i.e. [https://micropython.org/download/NUCLEO_F411RE/](https://micropython.org/download/NUCLEO_F411RE/) for both `.hex` and `.dfu` file.

### Mass erase

`st-flash`:
```shell
st-flash erase
```

`STM32CubeProgrammer`:
```shell
STM32_Programmer.sh -c port=SWD -e all
```

`dfu-util`:
```shell
# You can save the following as a file and run it with: sh file.sh
#!/bin/sh
set -x
echo -e -n "\xff" > ff.bin
dfu-util -s :mass-erase:force -a 0 -d 0483:df11 -D ff.bin
```

### STM32CubeProgrammer

In addtion to that, if you were using `STM32CubeProgrammer` with a GUI, everything should be very straight foward. And this is the most easy way to flash your device imo. There are 3 options available: `ST-Link, UART and USB` each corresponding to using a `st-link`, using a `uart-bridge` and using the built-in `dfu`.
