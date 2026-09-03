// WIZnet W5500-EVB-Pico2 + Seeed Wio-SX1262
// RP2350 (2 MB flash)

// Community/DIY board - no dedicated Meshtastic HardwareModel
#define PRIVATE_HW

#define ARDUINO_ARCH_AVR

// Onboard LED (GP25 on Pico 2)
#define LED_POWER PIN_LED

// Power monitoring
// GP24: VBUS sense - HIGH when USB is present (digital read)
// GP29: ADC3 measures VSYS/3 (200 kΩ / 100 kΩ divider, same as standard Pico 2)
#define EXT_PWR_DETECT 24
#define BATTERY_PIN 29
#define ADC_MULTIPLIER 3.0
#define BATTERY_SENSE_RESOLUTION_BITS 12
// No real battery - suppress false "battery at 100%" while USB powers VSYS
#define NO_BATTERY_LEVEL_ON_CHARGE

// Optional user button - connect a button between GP6 and GND
#define BUTTON_PIN 6
#define BUTTON_NEED_PULLUP

// GPS on UART1 (Serial2) - GP8 TX, GP9 RX
// GP8/GP9 belong to UART1, so we must use Serial2 (not the default Serial1/UART0).
// GP0/GP1 (UART0 defaults) are free but the firmware treats pin 0 as "not configured".
// GP4/GP5 occupied by I2C (SCL/SDA for BMP-280).
#define HAS_GPS 1
#define GPS_TX_PIN 8
#define GPS_RX_PIN 9
#define GPS_BAUDRATE 38400
#define GPS_SERIAL_PORT Serial2

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

// ---- W5500 Ethernet on SPI0 --------------------------------------------
#define HAS_ETHERNET 1
// Use the arduino-libraries/Ethernet stack (W5500) instead of RAK13800_W5100S
#define USE_ARDUINO_ETHERNET 1

#define ETH_SPI0_MISO 16
#define ETH_SPI0_SCK 18
#define ETH_SPI0_MOSI 19

#define PIN_ETHERNET_RESET 20
#define PIN_ETHERNET_SS 17
#define ETH_SPI_PORT SPI