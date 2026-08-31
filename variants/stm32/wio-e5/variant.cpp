#include "PinNames.h"
#include "stm32wlxx_hal_gpio_ex.h"
#include <Arduino.h>

// This override routes PA2/PA3 to USART2 (AF7) instead of LPUART1 (AF8).
// Currently also drops some of PinMap_UART_TX/RX which are unable to utilize on LoRa-E5 anyways.
// May restore LPUART1 on PC1/PC0, but this has its own quirks: only works at >9600 baud with LSE enabled,
// Also PC1/PC0 is not defined in variant.h, so if someone wants third-but-slow UART, some works are required.
//
// Details(to be refined): tl;dr: We can't use LPUART for our usecases(at least, for now&as far as i researched&tested)
// PA2/PA3 default to LPUART1 in the STM32WL Arduino core's PeripheralPins.c,
// but the Seeed LoRa-E5 datasheet (Table 1) documents them as USART2_TX/RX,
// Which is also correct as these pins' function can be alternated on the code.
//
// Even though, with LSE as the LPUART kernel clock, baud rates above ~10.9 kbaud are
// unreachable (BRR < 768), hangs while GPS auto-baud probing at boot,
// even worse...without LSE, using 48MHz master clock for LPUART does hangs too as it can't handle slower baud rate like 9k6.
// (min. is around 11.7 kbaud)
//
// So, we need to change PA2/PA3 to USART2 from LPUART1, and there is simple solution already available on stm32duino: PA_2_ALT1/PA_3_ALT1.
// Unfortunately, current GPS.cpp(and maybe others that handles GPIO's pin number) only handles pin numbers that's < 255 ,
// and these _ALT1 results in higher number, so until GPS.cpp and related codes' issues are discussed&sorted, this can be workaround.
//
// Explanations for asserts
// The static_asserts below catch any stm32duino AF renumbering that would
// silently invalidate this mapping, to safely abort the build if such change happened on upstream.
// While the coverage is questionable, need to take some time to ensure that.
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
