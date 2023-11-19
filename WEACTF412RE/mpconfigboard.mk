MCU_SERIES = f4
CMSIS_MCU = STM32F412Zx
AF_FILE = boards/stm32f412_af.csv
LD_FILES = boards/WEACTF412RE/stm32f412re.ld boards/common_ifs.ld

# Provide different variants for the downloads page.
ifeq ($(BOARD_VARIANT),DP)
MICROPY_FLOAT_IMPL=double
endif

ifeq ($(BOARD_VARIANT),THREAD)
CFLAGS += -DMICROPY_PY_THREAD=1
endif

ifeq ($(BOARD_VARIANT),DP_THREAD)
MICROPY_FLOAT_IMPL=double
CFLAGS += -DMICROPY_PY_THREAD=1
endif

ifeq ($(BOARD_VARIANT),NETWORK)
MICROPY_PY_NETWORK_WIZNET5K=5200
endif

# Micropython settings.
MICROPY_VFS_LFS2 ?= 1
