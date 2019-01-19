//
// Created by tully on 04/11/16.
//

#ifndef ROTATINGSTRIPESPATTERN_H
#define ROTATINGSTRIPESPATTERN_H

#include "led_config.h"
#include "lib8tion.h"

class RotatingStripesPattern {
public:
    void reset();

    void update(uint16_t deltaTime);
    void draw();

private:
    uint8_t _hue;
    int16_t _timeUntilHueShift;
    int16_t _pulseElapsed;
    int16_t _pulseOffset;

    static constexpr int8_t HueShiftMs = 60;
    static constexpr int16_t PulsePeriodMs = 2000;

    uint16_t getPulseWidth() const;
};


#endif //ROTATINGSTRIPESPATTERN_H
