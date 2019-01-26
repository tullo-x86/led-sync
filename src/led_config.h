
#ifndef LED_CONFIG_H
#define LED_CONFIG_H

#include <FastLED.h>

#define ARRAY0_LEDS 128
#define ARRAY1_LEDS 128

#define BUFFER_LENGTH (ARRAY0_LEDS + ARRAY1_LEDS)

namespace LED
{

class Array0
{
  public:
    static constexpr uint8_t Length = ARRAY0_LEDS;
    static constexpr uint8_t DataPin = 6;
    static struct CRGB *Buffer;
};

class Array1
{
  public:
    static constexpr uint8_t Length = ARRAY1_LEDS;
    static constexpr uint8_t DataPin = 7;
    static struct CRGB *Buffer;
};

enum class Step
{
    None,
    RadioRx,
    RadioTx,
    Update,
    Render,
    Present
};

class Indicator
{
  public:
    static constexpr uint8_t Pin = 9;

    static constexpr Step DebugMode = Step::Render;
};

} // namespace LED

#endif
