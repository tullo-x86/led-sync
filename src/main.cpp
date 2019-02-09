#include <Arduino.h>

#include <FastLED.h>

#include "led_config.h"
using namespace LED;

#include "WavesOverReef.h"
#include "DrawState.h"
#include "MathUtil.h"

struct CRGB frameBuffer[LED_BUFFER_LENGTH];
struct CRGB *Array0::Buffer = frameBuffer;
struct CRGB *Array1::Buffer = frameBuffer + Array0::Length;

WavesOverReef pattern;

template<Step STEP>
inline void beginIndicate() {
    if (Indicator::DebugMode == STEP) {
        digitalWrite(Indicator::Pin, HIGH);
    }
}
template<Step STEP>
inline void endIndicate() {
    if (Indicator::DebugMode == STEP) {
        digitalWrite(Indicator::Pin, LOW);
    }
}

DrawState drawState;

void initLeds()
{
    FastLED.addLeds<WS2811, Array0::DataPin, RGB>(Array0::Buffer, Array0::Length).setCorrection(Typical8mmPixel);
    FastLED.addLeds<WS2811, Array1::DataPin, RGB>(Array1::Buffer, Array1::Length).setCorrection(Typical8mmPixel);

    // Fill buffer with faint grey
    fill_solid(frameBuffer, LED_BUFFER_LENGTH, CRGB(8, 8, 8));

    // Fill each array with a unique colour
    fill_solid(Array0::Buffer, Array0::Length, CRGB(16, 0, 0));
    fill_solid(Array1::Buffer, Array1::Length, CRGB(0, 16, 0));

    //FastLED.setBrightness(144);
}

void setup()
{
    initLeds();
    pinMode(Indicator::Pin, OUTPUT);
}

uint32_t tsLast;
void loop()
{
    uint32_t tsNow = millis();

    drawState.tsCurrent = tsNow;
    drawState.analog = 16;

    beginIndicate<Step::Render>();
    pattern.draw(drawState);
    endIndicate<Step::Render>();

    beginIndicate<Step::Present>();
    FastLED.show();
    endIndicate<Step::Present>();
}
