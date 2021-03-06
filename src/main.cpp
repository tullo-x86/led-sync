#include <Arduino.h>

#include <FastLED.h>
#include <RadioHead.h>
#include <RH_RF69.h>
#include <NintendoExtensionCtrl.h>

#include "led_config.h"
using namespace LED;

#include "ShadowsInTheForest.h"
#include "ColorPairs.h"
#include "DrawState.h"
#include "MathUtil.h"

#include "RadioMesage.h"

struct CRGB frameBuffer[LED_BUFFER_LENGTH];
struct CRGB *Array0::Buffer = frameBuffer;
struct CHSV *Array0::HsvBuffer = reinterpret_cast<CHSV *>(Array0::Buffer);
struct CRGB *Array1::Buffer = frameBuffer + Array0::Length;
struct CHSV *Array1::HsvBuffer = reinterpret_cast<CHSV *>(Array1::Buffer);

ShadowsInTheForest pattern0;
ColorPairs pattern1;

inline void initIndicator()
{
    if (Indicator::DebugMode != LED::Step::None) 
    {
        pinMode(Indicator::Pin, OUTPUT);
    }
}

template <Step STEP>
inline void beginIndicate()
{
    if (Indicator::DebugMode == STEP)
    {
        digitalWrite(Indicator::Pin, HIGH);
    }
}
template <Step STEP>
inline void endIndicate()
{
    if (Indicator::DebugMode == STEP)
    {
        digitalWrite(Indicator::Pin, LOW);
    }
}

RH_RF69 radio;

// Key must be 16 bytes long:        "0123456789ABCDEF"
const char *const P_EncKey         = "InterrobangKrewe";
constexpr uint8_t L_EncKey = 16;
constexpr float RadioFrequency = 915.0;

uint8_t *txBuffer;
uint8_t *rxBuffer;
uint8_t incomingPacketLength;
RadioMessage message;

Nunchuk nunchuk;

DrawState drawState;

void initRadio()
{
    radio.init();

    txBuffer = reinterpret_cast<uint8_t*>(&message);
    rxBuffer = reinterpret_cast<uint8_t*>(&message);

    radio.setFrequency(RadioFrequency);
    radio.setEncryptionKey((uint8_t *)(P_EncKey));
    radio.setModemConfig(RH_RF69::GFSK_Rb19_2Fd38_4);
}

void initLeds()
{
    FastLED.addLeds<WS2811, Array0::DataPin, RGB>(Array0::Buffer, Array0::Length).setCorrection(Typical8mmPixel);
    FastLED.addLeds<WS2811, Array1::DataPin, RGB>(Array1::Buffer, Array1::Length).setCorrection(Typical8mmPixel);
    FastLED.addLeds<WS2811, Array0::AltDataPin, RGB>(Array0::Buffer, Array0::Length).setCorrection(Typical8mmPixel);
    FastLED.addLeds<WS2811, Array1::AltDataPin, RGB>(Array1::Buffer, Array1::Length).setCorrection(Typical8mmPixel);

    // Fill buffer with faint grey
    fill_solid(frameBuffer, LED_BUFFER_LENGTH, CRGB(8, 8, 8));

    // Fill each array with a unique colour
    fill_solid(Array0::Buffer, Array0::Length, CRGB(16, 0, 0));
    fill_solid(Array1::Buffer, Array1::Length, CRGB(0, 16, 0));

    //FastLED.setBrightness(144);
}

void initNunchuk()
{
    nunchuk.begin();

    nunchuk.connect();
}

uint32_t tsLastTransmission;
const uint32_t TransmitIntervalMs = 80;
uint32_t millisLastFrame;
uint32_t microsLastFrame;

void setup()
{
    initRadio();
    initLeds();
    initNunchuk();
    initIndicator();
    tsLastTransmission = millis();
    microsLastFrame = micros();
    message.tScale = 128;
}

bool triggerWasDown = false;
bool patternChangeWasDown = false;

void loop()
{
    const uint32_t microsNow = micros();
    const uint32_t microsElapsed = microsNow - microsLastFrame;
    microsLastFrame = microsNow;

    const uint8_t TIMESCALE_FACTOR = message.tScale;

    const uint32_t millisElapsed = (microsElapsed * TIMESCALE_FACTOR) >> (10 + 7);
    const uint32_t millisNow = millisLastFrame + millisElapsed;
    millisLastFrame = millisNow;

    const bool thisIsMasterUnit = nunchuk.update();
    if (thisIsMasterUnit)
    {
        message.tsNow = millisNow;
        bool importantUpdateThisFrame = false;

        if (!triggerWasDown && nunchuk.buttonZ())
        {
            importantUpdateThisFrame = true;
            message.tsPulled = millisNow;
            triggerWasDown = true;
        }
        else if (triggerWasDown && !nunchuk.buttonZ())
        {
            importantUpdateThisFrame = true;
            message.tsReleased = millisNow;
            triggerWasDown = false;
        }

        if (!patternChangeWasDown && nunchuk.buttonC())
        {
            importantUpdateThisFrame = true;
            message.idxPattern++;
            message.idxPattern %= 2;
        }

        patternChangeWasDown = nunchuk.buttonC();

        //drawState.analog = 0; // For demo
        message.analog = nunchuk.joyX(); // For "Ankey" controllers which max out early
        //drawState.analog = 255 - cos8(nunchuk.joyX() >> 1); // For genuine Nintendo controllers
        //drawState.analog = sin8(fractOf(drawState.tsCurrent, 20000)); // For demo

        message.tScale = nunchuk.joyY();

        uint32_t realMillisNow = millis();
        const bool shouldBroadcast = importantUpdateThisFrame || (realMillisNow - tsLastTransmission) > TransmitIntervalMs;
        if (shouldBroadcast)
        {
            beginIndicate<Step::RadioTx>();
            radio.send(txBuffer, RadioMessage::Size());
            radio.waitPacketSent();
            tsLastTransmission = realMillisNow;
            endIndicate<Step::RadioTx>();
        }
    }
    else
    {
        beginIndicate<Step::RadioRx>();
        uint8_t incomingPacketLength = RadioMessage::Size();
        if (radio.recv(rxBuffer, &incomingPacketLength)) {
            // noop
        } else {
            message.tsNow += millisElapsed;
        }
        endIndicate<Step::RadioRx>();
    }

    drawState.tsCurrent = message.tsNow;
    drawState.tsPulled = message.tsPulled;
    drawState.tsReleased = message.tsReleased;
    drawState.analog = message.analog;

    beginIndicate<Step::Render>();
    switch (message.idxPattern)
    {
        case 0:
            pattern0.draw(drawState);
            break;
    
        case 1:
            pattern1.draw(drawState);
            break;
        
        default:
            fill_solid(Array0::Buffer, Array0::Length, CRGB::Black);
            fill_solid(Array1::Buffer, Array1::Length, CRGB::Black);
            break;
    }
    endIndicate<Step::Render>();

    beginIndicate<Step::Present>();
    FastLED.show();
    endIndicate<Step::Present>();
}
