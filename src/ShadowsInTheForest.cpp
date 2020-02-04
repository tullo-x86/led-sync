//
// Created by tully on 2019-01-26.
//

#include "ShadowsInTheForest.h"
#include "MathUtil.h"

const CHSVPalette16 bgPal(
    CHSV( 96, 160, 255), // White-yellowish
    CHSV( 80, 192, 255), // Yellow
    CHSV(112, 192, 192), // Deeper green
    CHSV( 96, 255, 255)  // Yellowish
);

const CRGBPalette16 shadowsPal(
    CRGB::Grey,     CRGB::White,    CRGB::Black,    CRGB::Black,
    CRGB::Black,    CRGB::Black,    CRGB::Black,    CRGB::Black,
    CRGB::Black,    CRGB::Grey,     CRGB::Black,    CRGB::Black,
    CRGB::Black,    CRGB::Black,    CRGB::Grey,     CRGB::Black
);

void ShadowsInTheForest::draw(const DrawState &state) {
    constexpr uint8_t bgVal = 255;
    constexpr uint8_t fg1Val = 128;
    constexpr uint8_t fg2Val = 64;

    const uint8_t bgArray0Val = qadd8(64, scale8(bgVal, 255-state.analog));
    const uint8_t bgArray1Val = qadd8(64, scale8(bgVal, state.analog));
    const uint8_t fg1Array0Val = qadd8(64, scale8(fg1Val, 255-state.analog));
    const uint8_t fg2Array0Val = qadd8(64, scale8(fg2Val, 255-state.analog));
    const uint8_t fg1Array1Val = qadd8(64, scale8(fg1Val, state.analog));
    const uint8_t fg2Array1Val = qadd8(64, scale8(fg2Val, state.analog));

    uint8_t bgTimePhaseOffset = fractOf(state.tsCurrent, BGPalettePeriodMs);
    uint8_t fg1TimePhaseOffset = fractOf(state.tsCurrent, FG1PalettePeriodMs);
    uint8_t fg2TimePhaseOffset = fractOf(state.tsCurrent, FG2PalettePeriodMs);

    for (uint16_t pos = 0; pos < LED::Array0::Length; pos++)
    {
        fract8 bgPos = fractOf(pos, BGPaletteSpanPx);
        fract8 fg1Pos = fractOf(pos, FG1PaletteSpanPx);
        fract8 fg2Pos = fractOf(pos, FG2PaletteSpanPx);

        LED::Array0::Buffer[pos] = 
            ColorFromPalette(bgPal, bgPos + bgTimePhaseOffset, bgArray0Val) -
            ColorFromPalette(shadowsPal, fg1Pos + fg1TimePhaseOffset, fg1Array0Val) -
            ColorFromPalette(shadowsPal, fg2Pos - fg2TimePhaseOffset, fg2Array0Val);

        LED::Array1::Buffer[pos] = 
            ColorFromPalette(bgPal, bgPos + bgTimePhaseOffset + BGPaletteSpanPx/2, bgArray1Val) -
            ColorFromPalette(shadowsPal, fg1Pos + fg1TimePhaseOffset + FG1PaletteSpanPx/3, fg1Array1Val) -
            ColorFromPalette(shadowsPal, fg2Pos - fg2TimePhaseOffset + FG2PaletteSpanPx/3, fg2Array1Val);
    }
}
