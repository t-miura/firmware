#include <Arduino.h>

#if defined(ARDUINO_LORA_E5_MINI) || defined(ARDUINO_LORA_E5_DEV_BOARD)

#include "PinNames.h"

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

#endif
