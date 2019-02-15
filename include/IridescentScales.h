//
// Created by tully on 2019-02-04.
//

#ifndef IRIDESCENTSCALES_H
#define IRIDESCENTSCALES_H

#include "led_config.h"
#include "lib8tion.h"
#include "DrawState.h"

class IridescentScales {
public:

    IridescentScales();

    void draw(const DrawState &state);

private:
    CHSVPalette16 _bgPal;

    static constexpr int16_t BGPalettePeriodMs = 16000;
    static constexpr int16_t BGPaletteSpanPx = 256;

    static constexpr int32_t FlashHoldMsPerPxLength = 80;
    static constexpr int32_t FlashTravelMsPerPx = 5;
};

#endif //IRIDESCENTSCALES_H
