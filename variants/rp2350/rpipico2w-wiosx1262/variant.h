// #define RADIOLIB_CUSTOM_ARDUINO 1
// #define RADIOLIB_TONE_UNSUPPORTED 1
// #define RADIOLIB_SOFTWARE_SERIAL_UNSUPPORTED 1

#define ARDUINO_ARCH_AVR

#ifndef HAS_WIFI
#define HAS_WIFI 1
#endif

// default I2C pins:
// SDA = 4
// SCL = 5

// Recommended pins for SerialModule:
// txd = 8
// rxd = 9

#define EXT_NOTIFY_OUT 22
#define BUTTON_PIN 17

#define BATTERY_PIN 26
// ratio of voltage divider = 3.0 (R17=200k, R18=100k)
#define ADC_MULTIPLIER 3.1 // 3.0 + a bit for being optimistic
#define BATTERY_SENSE_RESOLUTION_BITS ADC_RESOLUTION

// ---- Wio-SX1262 on SPI1 -----------------------------------------
#define USE_SX1262

#undef LORA_SCK
#undef LORA_MISO
#undef LORA_MOSI
#undef LORA_CS

#define LORA_SCK 10  // SCK
#define LORA_MOSI 11 // MOSI
#define LORA_MISO 12 // MISO
#define LORA_CS 13   // NSS

#define LORA_DIO0 RADIOLIB_NC
#define LORA_RESET 15 // RESET
#define LORA_DIO1 14  // IRQ
#define LORA_DIO2 3   // RF-SW
#define LORA_DIO3 RADIOLIB_NC

#ifdef USE_SX1262
#define SX126X_CS LORA_CS
#define SX126X_DIO1 LORA_DIO1
#define SX126X_BUSY 2
#define SX126X_RESET LORA_RESET
// Slightly different than EBYTE E22-900M30S, refer XIAO ESP32-S3 variant for changes
#define SX126X_RXEN LORA_DIO2
#define SX126X_TXEN RADIOLIB_NC
#define SX126X_DIO2_AS_RF_SWITCH
#define SX126X_DIO3_TCXO_VOLTAGE 1.8
#endif