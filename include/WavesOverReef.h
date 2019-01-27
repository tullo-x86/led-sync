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
    static constexpr int16_t PalettePeriodMs = 10000;
    static constexpr int16_t PaletteSpanPx = 64;
};

constexpr uint16_t u16_255 = 0xff;
fract8 fractOf(uint16_t dividend, uint16_t divisor);

constexpr uint32_t u32_255 = 0xff;
fract8 fractOf(uint32_t dividend, uint32_t divisor);


#endif //WAVESOVERREEF_H
