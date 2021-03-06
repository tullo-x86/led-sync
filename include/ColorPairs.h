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
    static constexpr uint32_t HuePeriodMs = 30000;

    static constexpr int16_t Mask1LoopWidthFract = 64 << 8;
    static constexpr int16_t Mask1TransitionWidthFract = 4 << 8;
    static constexpr int16_t Mask1PeriodMs = 4000;

    static constexpr int16_t Mask2LoopWidthFract = 16 << 8;
    static constexpr int16_t Mask2TransitionWidthFract = 1 << 8;
    static constexpr int16_t Mask2PeriodMs = 900;

    static constexpr int16_t Mask3LoopWidthFract = 8 << 8;
    static constexpr int16_t Mask3TransitionWidthFract = 2 << 8;
    static constexpr int16_t Mask3PeriodMs = 1600;

    static constexpr int32_t FadeDurationMs = 255;
};

#endif //COLORPAIRS_H
