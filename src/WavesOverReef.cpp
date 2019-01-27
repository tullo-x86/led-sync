//
// Created by tully on 2019-01-26.
//

#include "WavesOverReef.h"

CRGBPalette16 bgPal(
    CHSV(144     , 180, 255),
    CHSV(HUE_AQUA, 255, 255),
    CHSV(112     , 128, 255),
    CHSV(HUE_AQUA, 255, 255)
);

void WavesOverReef::draw(const DrawState &state) {
    uint8_t bgTimePhaseOffset = fractOf(state.tsCurrent, PalettePeriodMs);

    for (uint16_t pos = 0; pos < LED::Array0::Length; pos++)
    {
        LED::Array0::Buffer[pos] = ColorFromPalette(bgPal, fractOf(pos, PaletteSpanPx) - bgTimePhaseOffset);
        LED::Array1::Buffer[pos] = ColorFromPalette(bgPal, fractOf(pos, PaletteSpanPx) - bgTimePhaseOffset);
    }
}

fract8 fractOf(uint16_t dividend, uint16_t divisor) {
    return (dividend * u16_255) / divisor;
}

fract8 fractOf(uint32_t dividend, uint32_t divisor) {
    return (dividend * u32_255) / divisor;
}
