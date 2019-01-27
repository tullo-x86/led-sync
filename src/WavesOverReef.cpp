//
// Created by tully on 2019-01-26.
//

#include "WavesOverReef.h"
#include "MathUtil.h"

const CHSVPalette16 bgPal(
    CHSV(128, 255, 255), // HUE_AQUA
    CHSV(144, 180, 255), // Blueish
    CHSV(116, 160, 255), // Greenish
    CHSV(128, 255, 255)  // HUE_AQUA
);

const CRGBPalette16 raysPal(
    CRGB::Grey,     CRGB::White,    CRGB::Grey,     CRGB::Black,
    CRGB::Black,    CRGB::Black,    CRGB::Black,    CRGB::Black,
    CRGB::Black,    CRGB::Grey,     CRGB::Grey,     CRGB::Black,
    CRGB::Black,    CRGB::Black,    CRGB::Black,    CRGB::Black
);

void WavesOverReef::draw(const DrawState &state) {
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

        LED::Array0::Buffer[pos] = 
            ColorFromPalette(bgPal, bgPos + bgTimePhaseOffset, bgVal) +
            ColorFromPalette(raysPal, fg1Pos + fg1TimePhaseOffset, fg1Array0Val) +
            ColorFromPalette(raysPal, fg2Pos - fg2TimePhaseOffset, fg2Array0Val);

        LED::Array1::Buffer[pos] = 
            ColorFromPalette(bgPal, bgPos + bgTimePhaseOffset + BGPaletteSpanPx/2, bgVal) +
            ColorFromPalette(raysPal, fg1Pos + fg1TimePhaseOffset + FG1PaletteSpanPx/3, fg1Array1Val) +
            ColorFromPalette(raysPal, fg2Pos - fg2TimePhaseOffset + FG2PaletteSpanPx/3, fg2Array1Val);
    }
}
