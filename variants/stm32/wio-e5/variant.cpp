#include "PinNames.h"
#include "stm32wlxx_hal_gpio_ex.h"
#include <Arduino.h>

// This override routes PA2/PA3 to USART2 (AF7) instead of LPUART1 (AF8).
// Currently also drops some of PinMap_UART_TX/RX which are unable to utilize on LoRa-E5 anyways.
// May restore LPUART1 on PC1/PC0, but this has its own quirks: only works at >9600 baud with LSE enabled,
// Also PC1/PC0 is not defined in variant.h, so if someone wants third-but-slow UART, some works are required.

// Details(to be refined)
// PA2/PA3 default to LPUART1 in the STM32WL Arduino core's PeripheralPins.c,
// but the Seeed LoRa-E5 datasheet (Table 1) documents them as USART2_TX/RX.
// With LSE as the LPUART kernel clock, baud rates above ~10.9 kbaud are
// unreachable (BRR < 768), hanging GPS auto-baud probing at boot.
// The static_asserts below catch any stm32duino AF renumbering that would
// silently invalidate this mapping.
static_assert(GPIO_AF7_USART2 == 0x07, "USART2 AF changed - review PA2/PA3 PinMap override in variant.cpp");
static_assert(GPIO_AF8_LPUART1 == 0x08, "LPUART1 AF changed - review PA2/PA3 PinMap override in variant.cpp");

#ifdef HAL_UART_MODULE_ENABLED
const PinMap PinMap_UART_TX[] = {{PA_2, USART2, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF7_USART2)},
                                 {PA_9, USART1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF7_USART1)},
                                 {PB_6, USART1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF7_USART1)},
                                 {NC, NP, 0}};

const PinMap PinMap_UART_RX[] = {{PA_3, USART2, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF7_USART2)},
                                 {PA_10, USART1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF7_USART1)},
                                 {PB_7, USART1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF7_USART1)},
                                 {NC, NP, 0}};
#endif
