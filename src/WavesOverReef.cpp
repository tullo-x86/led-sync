//
// Created by tully on 2019-01-26.
//

#include "WavesOverReef.h"

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
    constexpr uint8_t fg1Val = 32;
    constexpr uint8_t fg2Val = 24;
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
            ColorFromPalette(raysPal, fg1Pos + fg1TimePhaseOffset, fg1Val) +
            ColorFromPalette(raysPal, fg2Pos - fg2TimePhaseOffset, fg2Val);

        LED::Array1::Buffer[pos] = 
            ColorFromPalette(bgPal, bgPos + bgTimePhaseOffset + BGPaletteSpanPx/2, bgVal) +
            ColorFromPalette(raysPal, fg1Pos + fg1TimePhaseOffset + FG1PaletteSpanPx/3, fg1Val) +
            ColorFromPalette(raysPal, fg2Pos - fg2TimePhaseOffset + FG2PaletteSpanPx/3, fg2Val);
    }
}

fract8 fractOf(uint16_t dividend, uint16_t divisor) {
    return (dividend * u16_255) / divisor;
}

fract8 fractOf(uint32_t dividend, uint32_t divisor) {
    return (dividend * u32_255) / divisor;
}
