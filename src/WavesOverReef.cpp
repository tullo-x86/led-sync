//
// Created by tully on 2019-01-26.
//

#include "WavesOverReef.h"

void WavesOverReef::draw(const DrawState &state) {
    CRGBPalette16 bgPal(
        CHSV(HUE_BLUE, 255, 255),
        CHSV(HUE_AQUA, 255, 255),
        CHSV(HUE_GREEN, 255, 255),
        CHSV(HUE_AQUA, 255, 255)
    );

    // uint8_t bgTimePhaseOffset = (state.tsCurrent << 8) / PalettePeriodMs;
    uint8_t bgTimePhaseOffset = prop8(state.tsCurrent, PalettePeriodMs);

    for (uint16_t pos = 0; pos < LED::Array0::Length; pos++)
    {
        // LED::Array0::Buffer[pos] = ColorFromPalette(bgPal, pos * u16_255 / PaletteSpanPx);
        // LED::Array1::Buffer[pos] = ColorFromPalette(bgPal, pos * u16_255 / PaletteSpanPx);
        LED::Array0::Buffer[pos] = ColorFromPalette(bgPal, bgTimePhaseOffset + prop8(pos, PaletteSpanPx));
        LED::Array1::Buffer[pos] = ColorFromPalette(bgPal, bgTimePhaseOffset + prop8(pos, PaletteSpanPx));
    }
}

fract8 prop8(uint16_t dividend, uint16_t divisor) {
    return (dividend * u16_255) / divisor;
}

fract8 prop8(uint32_t dividend, uint32_t divisor) {
    return (dividend * u32_255) / divisor;
}
