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
    constexpr uint8_t fgVal = 64;
    uint8_t bgTimePhaseOffset = fractOf(state.tsCurrent, BGPalettePeriodMs);
    uint8_t fgTimePhaseOffset = fractOf(state.tsCurrent, FGPalettePeriodMs);

    for (uint16_t pos = 0; pos < LED::Array0::Length; pos++)
    {
        CRGB bgColor = ColorFromPalette(bgPal, fractOf(pos, BGPaletteSpanPx) - bgTimePhaseOffset, bgVal);

        LED::Array0::Buffer[pos] = bgColor +
            ColorFromPalette(raysPal, fractOf(pos, FGPaletteSpanPx) + fgTimePhaseOffset, fgVal);

        LED::Array1::Buffer[pos] = bgColor;
    }
}

fract8 fractOf(uint16_t dividend, uint16_t divisor) {
    return (dividend * u16_255) / divisor;
}

fract8 fractOf(uint32_t dividend, uint32_t divisor) {
    return (dividend * u32_255) / divisor;
}
