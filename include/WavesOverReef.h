//
// Created by tully on 04/11/16.
//

#ifndef WAVESOVERREEF_H
#define WAVESOVERREEF_H

#include "led_config.h"
#include "lib8tion.h"
#include "DrawState.h"

class WavesOverReef {
public:
    void draw(const DrawState &state);

private:
    static constexpr int16_t BGPalettePeriodMs = 10000;
    static constexpr int16_t BGPaletteSpanPx = 64;

    static constexpr int16_t FG1PalettePeriodMs = 3900;
    static constexpr int16_t FG1PaletteSpanPx = 16;

    static constexpr int16_t FG2PalettePeriodMs = 2900;
    static constexpr int16_t FG2PaletteSpanPx = 32;
};

#endif //WAVESOVERREEF_H
