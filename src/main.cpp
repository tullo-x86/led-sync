#include <Arduino.h>

#include <FastLED.h>
#include <RadioHead.h>
#include <RH_RF69.h>
#include <NintendoExtensionCtrl.h>

#include "led_config.h"
using namespace LED;

#include "playlist.h"
#include "RotatingStripesPattern.h"

struct CRGB frameBuffer[BUFFER_LENGTH];
struct CRGB *Array0::Buffer = frameBuffer;
struct CRGB *Array1::Buffer = frameBuffer + Array0::Length;

Playlist<RotatingStripesPattern> playlist;

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

RH_RF69 radio;

// Key must be 16 bytes long:        "0123456789ABCDEF"
const char *const P_EncKey PROGMEM = "InterrobangKrewe";
constexpr uint8_t L_EncKey = 16;
constexpr float RadioFrequency = 915.0;

Nunchuk nunchuk;

void initRadio()
{
    radio.init();

    char encryptionKey[L_EncKey];
    strncpy_P(encryptionKey, P_EncKey, L_EncKey);

    radio.setFrequency(RadioFrequency);
    radio.setEncryptionKey((uint8_t *)(encryptionKey));
    radio.setModemConfig(RH_RF69::GFSK_Rb19_2Fd38_4);

    playlist.goToIndex(0);
}

void initLeds()
{
    FastLED.addLeds<WS2811, Array0::DataPin, RGB>(Array0::Buffer, Array0::Length).setCorrection(Typical8mmPixel);
    FastLED.addLeds<WS2811, Array1::DataPin, RGB>(Array1::Buffer, Array1::Length).setCorrection(Typical8mmPixel);

    // Fill buffer with faint grey
    fill_solid(frameBuffer, BUFFER_LENGTH, CRGB(8, 8, 8));

    // Fill each array with a unique colour
    fill_solid(Array0::Buffer, Array0::Length, CRGB(16, 0, 0));
    fill_solid(Array1::Buffer, Array1::Length, CRGB(0, 16, 0));
}

void initNunchuk() {
    nunchuk.begin();

    nunchuk.connect();
}

void setup()
{
    initRadio();
    initLeds();
    //initNunchuk();
    pinMode(Indicator::Pin, OUTPUT);
}

uint32_t lastFrameTime;
void loop()
{
    uint32_t currentFrameTime = millis();
    uint16_t deltaT = currentFrameTime - lastFrameTime;
    lastFrameTime = currentFrameTime;

    beginIndicate<Step::Update>();
    playlist.dispatchUpdate(deltaT);
    endIndicate<Step::Update>();

    beginIndicate<Step::Render>();
    playlist.dispatchDraw();
    endIndicate<Step::Render>();

    beginIndicate<Step::Present>();
    FastLED.show();
    endIndicate<Step::Present>();
}
