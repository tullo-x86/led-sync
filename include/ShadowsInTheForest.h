//
// Created by tully on 2020-01-25.
//

#ifndef SHADOWSINTHEFOREST_H
#define SHADOWSINTHEFOREST_H

#include "led_config.h"
#include "lib8tion.h"
#include "DrawState.h"

class ShadowsInTheForest {
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

#endif //SHADOWSINTHEFOREST
