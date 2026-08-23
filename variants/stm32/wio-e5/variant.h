/*
Wio-E5 mini (formerly LoRa-E5 mini)
https://www.seeedstudio.com/LoRa-E5-mini-STM32WLE5JC-p-4869.html
https://www.seeedstudio.com/LoRa-E5-Wireless-Module-p-4745.html
*/

/*
This variant is a work in progress.
Do not expect a working Meshtastic device with this target.
*/

#ifndef _VARIANT_WIOE5_
#define _VARIANT_WIOE5_

#define USE_STM32WLx

#define LED_POWER PB5
#define LED_STATE_ON 0

#define WIO_E5

#define HAS_LSE 1
#define STM32WL_LSE_DRIVE RCC_LSEDRIVE_LOW

#define HAS_SENSOR 1

#define HAS_GPS 1
#define GPS_TX_PIN PA2
#define GPS_RX_PIN PA3

#endif
