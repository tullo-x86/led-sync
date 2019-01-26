//
// Created by tully on 04/11/16.
//

#ifndef ROTATINGSTRIPESPATTERN_H
#define ROTATINGSTRIPESPATTERN_H

#include "led_config.h"
#include "lib8tion.h"
#include "DrawState.h"

class RotatingStripesPattern {
public:
    void draw(const DrawState &state);

private:
    static constexpr int8_t HueShiftMs = 60;
    static constexpr int16_t ValWavePeriodMs = 2000;
};


#endif //ROTATINGSTRIPESPATTERN_H
