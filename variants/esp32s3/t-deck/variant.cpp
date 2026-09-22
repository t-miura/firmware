#include "variant.h"
#include "Arduino.h"

void earlyInitVariant()
{
    // GPIO10 manages all peripheral power supplies
    // Turn on peripheral power immediately after MUC starts.
    // If some boards are turned on late, ESP32 will reset due to low voltage.
    // ESP32-C3(Keyboard) , MAX98357A(Audio Power Amplifier) ,
    // TF Card , Display backlight(AW9364DNR) , AN48841B(Trackball) , ES7210(Decoder)
    pinMode(KB_POWERON, OUTPUT);
    digitalWrite(KB_POWERON, HIGH);

    // T-Deck has all three SPI peripherals (TFT, SD, LoRa) attached to the same SPI bus.
    // Deselect all CS pins first so NSS is held HIGH and the bus is quiescent during reset.
    pinMode(LORA_CS, OUTPUT);
    digitalWrite(LORA_CS, HIGH);
    pinMode(SDCARD_CS, OUTPUT);
    digitalWrite(SDCARD_CS, HIGH);
    pinMode(TFT_CS, OUTPUT);
    digitalWrite(TFT_CS, HIGH);

    // Hardware reset SX1262 so DIO1 drops LOW and stops any pending IRQs.
    // CS pins are already HIGH above so NSS is deselected while NRESET is asserted.
    pinMode(LORA_RESET, OUTPUT);
    digitalWrite(LORA_RESET, LOW);
    delay(10);
    digitalWrite(LORA_RESET, HIGH);

    // Allow peripherals (Keyboard C3, SD card, SX1262 STDBY_RC) to fully settle
    delay(100);
}
