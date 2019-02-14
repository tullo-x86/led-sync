
#ifndef LED_CONFIG_H
#define LED_CONFIG_H

#include <FastLED.h>

#define ARRAY0_LEDS 128
#define ARRAY1_LEDS 128

#define LED_BUFFER_LENGTH (ARRAY0_LEDS + ARRAY1_LEDS)

namespace LED
{

class Array0
{
  public:
    static constexpr uint8_t Length = ARRAY0_LEDS;
    static constexpr uint8_t DataPin = 6;
    static constexpr uint8_t AltDataPin = 8;
    static struct CRGB *Buffer;
    static struct CHSV *HsvBuffer;
};

class Array1
{
  public:
    static constexpr uint8_t Length = ARRAY1_LEDS;
    static constexpr uint8_t DataPin = 7;
    static constexpr uint8_t AltDataPin = 9;
    static struct CRGB *Buffer;
    static struct CHSV *HsvBuffer;
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

    static constexpr Step DebugMode = Step::None;
};

} // namespace LED

#endif
