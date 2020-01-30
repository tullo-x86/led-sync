#include "ColorPairs.h"
#include "MathUtil.h"

ColorPairs::ColorPairs() 
{
    //
}

// index: Pixel index
// phaseOffset (fract): Time offset for animation
// pulseWidth (fract): Width of whole animation loop
// transitionWidth (fract): Width of ease between light/dark. More = smooth. Less = sharp.
uint8_t mask(uint16_t index, int16_t phaseOffset, int16_t pulseWidth, int16_t transitionWidth) {

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

void ColorPairs::draw(const DrawState &state)
{
    const uint8_t baseHue = fractOf(state.tsCurrent, HuePeriodMs);

    const int32_t waveOffsetFract = (state.tsCurrent % WavePeriodMs) * WaveLoopWidthFract / WavePeriodMs;
    const int32_t maskOffsetFract = (state.tsCurrent % MaskPeriodMs) * MaskLoopWidthFract / MaskPeriodMs;

    const uint8_t waveVal = mask(128, waveOffsetFract, WaveLoopWidthFract, WaveTransitionWidthFract);
    const uint8_t channel0Wave = qsub8(waveVal, 128) * 2;
    const uint8_t channel1Wave = 255 - (qadd8(waveVal, 128) - 128) * 2;

    for (uint16_t pos = 0; pos < LED::Array0::Length; pos++)
    {
        uint8_t maskVal = mask(pos, -maskOffsetFract, MaskLoopWidthFract, MaskTransitionWidthFract);

        LED::Array0::HsvBuffer[pos] = CHSV(baseHue + 00, 255, scale8(channel0Wave, maskVal));
        LED::Array1::HsvBuffer[pos] = CHSV(baseHue + 64, 255, scale8(channel1Wave, maskVal));
    }

    hsv2rgb_rainbow(LED::Array0::HsvBuffer, LED::Array0::Buffer, LED::Array0::Length);
    hsv2rgb_rainbow(LED::Array1::HsvBuffer, LED::Array1::Buffer, LED::Array1::Length);
}
