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

    const int32_t mask1OffsetFract = (state.tsCurrent % Mask1PeriodMs) * Mask1LoopWidthFract / Mask1PeriodMs;
    const int32_t mask2OffsetFract = (state.tsCurrent % Mask2PeriodMs) * Mask2LoopWidthFract / Mask2PeriodMs;
    const int32_t mask3OffsetFract = (state.tsCurrent % Mask3PeriodMs) * Mask3LoopWidthFract / Mask3PeriodMs;

    // TODO: Make this "split L/R" generic
    const uint8_t val0Base = qsub8(state.analog, 128) * 2;
    const uint8_t val1Base = 255 - (qadd8(state.analog, 128) - 128) * 2;

    const bool isCharging = (state.tsPulled > state.tsReleased);
    const int32_t sinceTriggerChange = isCharging
        ? (state.tsCurrent - state.tsPulled)    // Fade-in
        : (state.tsCurrent - state.tsReleased); // Fade-out

    uint8_t fadeAmt = 0;
    if (!isCharging)
    {
        fadeAmt = min(255, sinceTriggerChange * 255 / FadeDurationMs);
    }
    else
    {
        fadeAmt = 255 - min(255, sinceTriggerChange * 255 / FadeDurationMs);
    }

    for (uint16_t pos = 0; pos < LED::Array0::Length; pos++)
    {
        const uint8_t mask1Val0 = mask(pos, -mask1OffsetFract, Mask1LoopWidthFract, Mask1TransitionWidthFract);
        const uint8_t mask1Val1 = mask(pos, (Mask1LoopWidthFract/2) - mask1OffsetFract, Mask1LoopWidthFract, Mask1TransitionWidthFract);
        const uint8_t mask2Val = mask(pos, mask2OffsetFract, Mask2LoopWidthFract, Mask2TransitionWidthFract);
        const uint8_t mask3Val = mask(pos, mask3OffsetFract, Mask3LoopWidthFract, Mask3TransitionWidthFract);
        const uint8_t maskVal0 = scale8(mask1Val0, qadd8(64, scale8(mask2Val, mask3Val)));
        const uint8_t maskVal1 = scale8(mask1Val1, qadd8(64, scale8(mask2Val, mask3Val)));

        LED::Array0::HsvBuffer[pos] = CHSV(baseHue + 00, 255, scale8(maskVal0, qadd8(val0Base, fadeAmt)));
        LED::Array1::HsvBuffer[pos] = CHSV(baseHue + 64, 255, scale8(maskVal1, qadd8(val1Base, fadeAmt)));
    }

    hsv2rgb_rainbow(LED::Array0::HsvBuffer, LED::Array0::Buffer, LED::Array0::Length);
    hsv2rgb_rainbow(LED::Array1::HsvBuffer, LED::Array1::Buffer, LED::Array1::Length);
}
