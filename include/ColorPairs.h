// Created by tully on 2020-01-26

#ifndef COLORPAIRS_H
#define COLORPAIRS_H

#include "led_config.h"
#include "lib8tion.h"
#include "DrawState.h"

class ColorPairs
{
public:

    ColorPairs();

    void draw(const DrawState &state);

private:
    static constexpr int16_t HuePeriodMs = 16000;

    static constexpr int16_t MaskPulseWidthFract = 16 << 8; // 16px
    static constexpr int16_t MaskTransitionWidthFract = 8 << 8; // 8px
    static constexpr int16_t MaskTotalWidthFract = (MaskPulseWidthFract + MaskTransitionWidthFract) * 2;
    static constexpr int16_t MaskPeriodMs = 1000;
};

#endif //COLORPAIRS_H