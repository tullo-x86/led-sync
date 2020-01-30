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

    static constexpr int16_t MaskLoopWidthFract = 127 << 8;
    static constexpr int16_t MaskTransitionWidthFract = 16 << 8;
    static constexpr int16_t MaskPeriodMs = 1000;

    static constexpr int16_t WaveLoopWidthFract = 16 << 8;
    static constexpr int16_t WaveTransitionWidthFract = 1 << 8;
    static constexpr int16_t WavePeriodMs = 4000;
};

#endif //COLORPAIRS_H
