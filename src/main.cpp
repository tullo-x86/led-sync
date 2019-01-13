#include <Arduino.h>

#include <FastLED.h>
#include <RadioHead.h>
#include <RH_RF69.h>

#include "led_config.h"

RH_RF69 radio;

CRGB frameBuffer[BUFFER_LENGTH];

// Encryption key must = 16 bytes "0123456789ABCDEF"
const char *const encryptionKey = "InterrobangKrewe";

const float RadioFrequency = 915.0;

void initRadio()
{
    radio.init();

    radio.setFrequency(RadioFrequency);
    radio.setEncryptionKey((uint8_t *)(encryptionKey));
    radio.setModemConfig(RH_RF69::GFSK_Rb19_2Fd38_4);
}

void initLeds()
{
    FastLED.addLeds<WS2811, ARRAY0_DATA_PIN, RGB>(frameBuffer, ARRAY0_LEDS).setCorrection(Typical8mmPixel);
    FastLED.addLeds<WS2811, ARRAY1_DATA_PIN, RGB>(frameBuffer, ARRAY1_LEDS).setCorrection(Typical8mmPixel);

    // Fill array with faint grey
    fill_solid(frameBuffer, BUFFER_LENGTH, CRGB(8, 8, 8));
}

void setup()
{
    initRadio();
    initLeds();
    pinMode(INPUT_PIN, INPUT_PULLUP);

    FastLED.show();
}

void loop()
{
    FastLED.show();
}
