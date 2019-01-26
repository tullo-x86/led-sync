//
// Created by tully on 04/11/16.
//

#include "RotatingStripesPattern.h"

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

void RotatingStripesPattern::draw(const DrawState &state) {
    // The V-wave, bringing global brightness up and down
    uint32_t valElapsed = state.tsCurrent % ValWavePeriodMs;
    uint8_t valPhase = (uint32_t)valElapsed * 255 / ValWavePeriodMs;
    // uint8_t val = 32 + scale8(sin8(valPhase), (255-32));
    uint8_t val = 128;

    uint8_t hue = (state.tsCurrent / HueShiftMs);

    const int16_t pulseWidth = 3400;
    int16_t pulseOffset = state.tsCurrent / pulseWidth;
    int16_t transitionWidth = pulseWidth / 4;

    for (uint8_t i = 0; i < LED::Array0::Length; ++i) {
        LED::Array0::Buffer[i] = CHSV(hue + 0x80, 255, scale8(mask(i, pulseOffset, pulseWidth, transitionWidth), val));
        LED::Array1::Buffer[i] = CHSV(hue + 0x00, 255, scale8(mask(i, pulseOffset, pulseWidth, transitionWidth), val));
    }
}

//uint16_t RotatingStripesPattern::getPulseWidth() const { return LED::Array1::Length * (uint16_t)256 / 6; }
