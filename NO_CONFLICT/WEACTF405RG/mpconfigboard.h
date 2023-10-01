#define MICROPY_HW_BOARD_NAME       "WeAct-STM32F405"
#define MICROPY_HW_MCU_NAME         "STM32F405RG"

// Disabled network realted functions to save space
// Note STM32F405-series does not have ETH-interface
// #define MICROPY_PY_SOCKET                       (0)
// #define MICROPY_PY_NETWORK                      (0)
// #define MICROPY_PY_ONEWIRE                      (0)

// Enabling hardware related features
// For more details check mpconfigboard_common.h
#define MICROPY_HW_HAS_FLASH        (1)
#define MICROPY_HW_HAS_SWITCH       (1)
#define MICROPY_HW_HAS_MMA7660      (0)
#define MICROPY_HW_HAS_LCD          (0)
#define MICROPY_HW_ENABLE_RNG       (1)
#define MICROPY_HW_ENABLE_RTC       (1)
#define MICROPY_HW_ENABLE_SERVO     (1) // PA0-PA3, you might want to disable USART2
#define MICROPY_HW_ENABLE_ADC       (1)
#define MICROPY_HW_ENABLE_DAC       (1)
#define MICROPY_HW_ENABLE_USB       (1)
#define MICROPY_HW_ENABLE_TIMER     (1)
#define MICROPY_HW_ENABLE_SDCARD    (1)
#define MICROPY_HW_ENABLE_MMCARD    (0)

// HSE is 8MHz, this gives 168MHz sysclock and 48MHz for USB.
#define MICROPY_HW_CLK_PLLM         (8)
#define MICROPY_HW_CLK_PLLN         (336)
#define MICROPY_HW_CLK_PLLP         (RCC_PLLP_DIV2)
#define MICROPY_HW_CLK_PLLQ         (7)

// Pyboard lite has an optional 32kHz crystal
#define MICROPY_HW_RTC_USE_LSE      (1)
#define MICROPY_HW_RTC_USE_US       (0)
#define MICROPY_HW_RTC_USE_CALOUT   (1)

// UART config, 
// USART2 and USART6 are unipin across all 3 definitions.
// USARTs
#define MICROPY_HW_UART1_TX         (pin_A9) // Valid: PA9, PB6
#define MICROPY_HW_UART1_RX         (pin_A10) // Valid: PA10, PB7
#define MICROPY_HW_UART2_TX         (pin_A2) // Valid: PA2
#define MICROPY_HW_UART2_RX         (pin_A3) // Valid: PA3
#define MICROPY_HW_UART3_TX         (pin_B10) // Valid: PB10, PC10
#define MICROPY_HW_UART3_RX         (pin_B11) // Valid: PB11, PC11
#define MICROPY_HW_UART6_TX         (pin_C6) // Valid: PC6
#define MICROPY_HW_UART6_RX         (pin_C7) // Valid: PC7
// UARTs
#define MICROPY_HW_UART4_TX         (pin_A1) // Valid: PA1, PC11
#define MICROPY_HW_UART4_RX         (pin_A0) // Valid: PA0, PC10
// Disabled because PC12 and PD2 are taken by SD Card.
// #define MICROPY_HW_UART5_TX         (pin_C12) // Valid: PC12
// #define MICROPY_HW_UART5_RX         (pin_D2) // Valid: PD2

#define MICROPY_HW_UART_REPL        PYB_UART_6
#define MICROPY_HW_UART_REPL_BAUD   115200

// I2C buses
// I2C1 are unipin across all 3 definitions.
#define MICROPY_HW_I2C1_SCL         (pin_B8) // Valid: PB6, PB8
#define MICROPY_HW_I2C1_SDA         (pin_B9) // Valid: PB7, PB9
#define MICROPY_HW_I2C2_SCL         (pin_B10) // Valid: PB10
#define MICROPY_HW_I2C2_SDA         (pin_B11) // Valid: PB11
// Disabled because A8 and C9 is taken by SD Card.
// #define MICROPY_HW_I2C3_SCL         (pin_A8) // Valid: PA8
// #define MICROPY_HW_I2C3_SDA         (pin_C9) // Valid: PC9

// SPI buses
// SPI1, SPI2 and SPI3 are unipin across all 3 definitions.
#define MICROPY_HW_SPI1_NSS         (pin_A4) // Valid: PA4, PA15
#define MICROPY_HW_SPI1_SCK         (pin_A5) // Valid: PA5, PB3
#define MICROPY_HW_SPI1_MISO        (pin_A6) // Valid: PA6, PB4
#define MICROPY_HW_SPI1_MOSI        (pin_A7) // Valid: PA7, PB5
#define MICROPY_HW_SPI2_NSS         (pin_B12) // Valid: PB9, PB12
#define MICROPY_HW_SPI2_SCK         (pin_B13) // Valid: PB10, PB13
#define MICROPY_HW_SPI2_MISO        (pin_B14) // Valid: PB14, PC2
#define MICROPY_HW_SPI2_MOSI        (pin_B15) // Valid: PB15, PC3
// Currently interferes with CAN2.
#define MICROPY_HW_SPI3_NSS         (pin_A15) // Valid: PA4, PA15
#define MICROPY_HW_SPI3_SCK         (pin_B3) // Valid: PB3, PC10
#define MICROPY_HW_SPI3_MISO        (pin_B4) // Valid: PB4, PC11
#define MICROPY_HW_SPI3_MOSI        (pin_B5) // Valid: PB5, PC12

// CAN buses
#define MICROPY_HW_CAN1_TX          (pin_B9) // Valid: PA12, PB9
#define MICROPY_HW_CAN1_RX          (pin_B8) // Valid: PA11, PB8
// Currently interferes with SPI3.
// #define MICROPY_HW_CAN2_TX          (pin_B6) // Valid: PB6, PB13
// #define MICROPY_HW_CAN2_RX          (pin_B5) // Valid: PB5, PB12

// SD Card SDMMC
#define MICROPY_HW_SDCARD_CK        (pin_C12)
#define MICROPY_HW_SDCARD_CMD       (pin_D2)
#define MICROPY_HW_SDCARD_D0        (pin_C8)
#define MICROPY_HW_SDCARD_D1        (pin_C9)
#define MICROPY_HW_SDCARD_D2        (pin_C10)
#define MICROPY_HW_SDCARD_D3        (pin_C11)
#define MICROPY_HW_SDCARD_DETECT_PIN (pin_A8)
#define MICROPY_HW_SDCARD_DETECT_PULL (GPIO_PULLUP)
#define MICROPY_HW_SDCARD_DETECT_PRESENT (GPIO_PIN_SET)
#define MICROPY_HW_SDCARD_MOUNT_AT_BOOT (0)

// USRSW has no pullup or pulldown, and pressing the switch makes the input go low
#define MICROPY_HW_USRSW_PIN        (pin_C13)
#define MICROPY_HW_USRSW_PULL       (GPIO_PULLUP)
#define MICROPY_HW_USRSW_EXTI_MODE  (GPIO_MODE_IT_RISING)
#define MICROPY_HW_USRSW_PRESSED    (0)

// LEDs
#define MICROPY_HW_LED1             (pin_B2) // blue
#define MICROPY_HW_LED_ON(pin)      (mp_hal_pin_high(pin))
#define MICROPY_HW_LED_OFF(pin)     (mp_hal_pin_low(pin))

// USB config
#define MICROPY_HW_USB_FS           (1)
#define MICROPY_HW_FLASH_FS_LABEL   "STM32F405RG"

#define MICROPY_HW_USB_MANUFACTURER_STRING      "WeActStudio"
#define MICROPY_HW_USB_PRODUCT_FS_STRING        "STM32F405RG Comm Port (FS Mode)"
#define MICROPY_HW_USB_CONFIGURATION_FS_STRING  "USB Config"
#define MICROPY_HW_USB_INTERFACE_FS_STRING      "USB Interface"
// This is to save a tiny little space taken by strings.
#define MICROPY_HW_USB_PRODUCT_HS_STRING        ""
#define MICROPY_HW_USB_CONFIGURATION_HS_STRING  ""
#define MICROPY_HW_USB_INTERFACE_HS_STRING      ""
