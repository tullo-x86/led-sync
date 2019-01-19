//
// Created by tully on 04/11/16.
//

#include "RotatingStripesPattern.h"

void RotatingStripesPattern::reset() {
    _hue = random8();
    _pulseElapsed = 0;
    _timeUntilHueShift = 0;
    _pulseOffset = 0;
}

void RotatingStripesPattern::update(uint16_t deltaTime) {
    _timeUntilHueShift -= deltaTime;
    if (_timeUntilHueShift < 0) {
        _hue++;
        _timeUntilHueShift = HueShiftMs;
    }

    _pulseElapsed += deltaTime;
    if (_pulseElapsed > PulsePeriodMs) _pulseElapsed = 0;

    _pulseOffset += deltaTime;
    _pulseOffset %= getPulseWidth();
}

uint8_t mask(uint8_t index, int16_t phaseOffset, int16_t pulseWidth, int16_t transitionWidth) {

    int32_t theta = (phaseOffset + index * 256) % pulseWidth;

    if (theta < transitionWidth) {
        // Phase 1 - upward
        return ease8InOutQuad(theta * 255 / transitionWidth);
    }
    else if (theta < pulseWidth / 2) {
        // Phase 2 - bright
        return 255;
    }
    else if (theta < ((pulseWidth / 2) + transitionWidth)) {
        // Phase 3 - downward
        return ease8InOutQuad((int16_t)255 - ((theta - (pulseWidth / 2)) * 255 / transitionWidth));
    }
    else {
        // Phase 4 - dim
        return 0;
    }
}

void RotatingStripesPattern::draw() {
    uint8_t pulsePhase = (int32_t)_pulseElapsed * 255 / PulsePeriodMs;
    uint8_t val = scale8(sin8(pulsePhase), 223) + 32;

    int16_t pulseWidth = getPulseWidth();
    int16_t transitionWidth = pulseWidth / 4;

    for (uint8_t i = 0; i < LED::Array1::Length; ++i) {
        LED::Array1::Buffer[i] = CHSV(_hue, 255, scale8(mask(i, _pulseOffset, pulseWidth, transitionWidth), val));
    }
}

uint16_t RotatingStripesPattern::getPulseWidth() const { return LED::Array1::Length * (uint16_t)256 / 6; }
