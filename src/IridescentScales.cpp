//
// Created by tully on 2019-01-26.
//

#include "IridescentScales.h"
#include "MathUtil.h"

IridescentScales::IridescentScales()
: _bgPal(CHSV(180, 255, 255)) {
    const CHSV c1 = CHSV(149, 150, 200); // i-Blue
    const CHSV c2 = CHSV(235, 110, 210); // i-Salmon
    const CHSV c3 = CHSV( 39, 135, 235); // i-Gold
    const CHSV c4 = CHSV(118, 105, 206); // i-Greenish

    _bgPal = CHSVPalette16(
        c1, c1, c1, c1,
        c2, c2, c2, c2,
        c3, c3, c3, c3,
        c4, c4, c4, c4);
}

const CRGBPalette16 raysPal(
    CRGB::Black,     CRGB::Black,    CRGB::Black,     CRGB::Black,
    CRGB::Black,    CRGB::Black,    CRGB::Black,    CRGB::Black,
    CRGB::Black,    CRGB::Black,     CRGB::Black,     CRGB::Black,
    CRGB::Black,    CRGB::Black,    CRGB::Black,    CRGB::Black
);

void IridescentScales::draw(const DrawState &state) {
    constexpr uint8_t bgVal = 128;
    constexpr uint8_t fg1Val = 64;
    constexpr uint8_t fg2Val = 32;

    const uint8_t fg1Array0Val = scale8(fg1Val, 255-state.analog);
    const uint8_t fg2Array0Val = scale8(fg2Val, 255-state.analog);
    const uint8_t fg1Array1Val = scale8(fg1Val, state.analog);
    const uint8_t fg2Array1Val = scale8(fg2Val, state.analog);

    uint8_t bgTimePhaseOffset = fractOf(state.tsCurrent, BGPalettePeriodMs);
    uint8_t fg1TimePhaseOffset = fractOf(state.tsCurrent, FG1PalettePeriodMs);
    uint8_t fg2TimePhaseOffset = fractOf(state.tsCurrent, FG2PalettePeriodMs);

    for (uint16_t pos = 0; pos < LED::Array0::Length; pos++)
    {
        fract8 bgPos = fractOf(pos, BGPaletteSpanPx);
        fract8 fg1Pos = fractOf(pos, FG1PaletteSpanPx);
        fract8 fg2Pos = fractOf(pos, FG2PaletteSpanPx);

        LED::Array0::HsvBuffer[pos] = 
            ColorFromPalette(_bgPal, bgPos + bgTimePhaseOffset, bgVal);

        LED::Array1::HsvBuffer[pos] = 
            ColorFromPalette(_bgPal, bgPos + bgTimePhaseOffset, bgVal);
    }

    hsv2rgb_rainbow(LED::Array0::HsvBuffer, LED::Array0::Buffer, LED::Array0::Length);
    hsv2rgb_rainbow(LED::Array1::HsvBuffer, LED::Array1::Buffer, LED::Array1::Length);
}
