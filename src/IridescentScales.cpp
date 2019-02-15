//
// Created by tully on 2019-01-26.
//

#include "IridescentScales.h"
#include "MathUtil.h"

IridescentScales::IridescentScales()
    : _bgPal(CHSV(180, 255, 255))
{
    const CHSV c1 = CHSV(149, 150, 200); // i-Blue
    const CHSV c2 = CHSV(235, 110, 210); // i-Salmon
    const CHSV c3 = CHSV(39, 135, 235);  // i-Gold
    const CHSV c4 = CHSV(118, 105, 206); // i-Greenish

    _bgPal = CHSVPalette16(
        c1, c1, c1, c1,
        c2, c2, c2, c2,
        c3, c3, c3, c3,
        c4, c4, c4, c4);
}

void IridescentScales::draw(const DrawState &state)
{
    constexpr uint8_t bgVal = 128;

    uint8_t bgTimePhaseOffset = fractOf(state.tsCurrent, BGPalettePeriodMs);

    for (uint16_t pos = 0; pos < LED::Array0::Length; pos++)
    {
        fract8 bgPos = fractOf(pos, BGPaletteSpanPx);

        LED::Array0::HsvBuffer[pos] =
            ColorFromPalette(_bgPal, bgPos + bgTimePhaseOffset, bgVal);

        LED::Array1::HsvBuffer[pos] =
            ColorFromPalette(_bgPal, bgPos + bgTimePhaseOffset, bgVal);
    }

    bool isCharging = (state.tsPulled > state.tsReleased);

    uint32_t maxDuration = FlashHoldMsPerPxLength * LED::Array0::Length;
    uint32_t duration = isCharging
                            ? (state.tsCurrent - state.tsPulled)   // Charging
                            : (state.tsReleased - state.tsPulled); // Discharging

    // How big is the flash?
    uint8_t flashLength = (duration < maxDuration) ? (duration / FlashHoldMsPerPxLength) : 0;

    if (flashLength > 0)
    {
        // How far can the flash travel?
        const uint32_t flash0MaxPos = LED::Array0::Length - flashLength;
        const uint32_t flash1MaxPos = LED::Array1::Length - flashLength;

        int32_t flash0Pos = -1;
        int32_t flash1Pos = -1;

        // Where is the flash right now?
        const uint32_t flashPxMovedSinceRelease = isCharging ? 0 : (state.tsCurrent - state.tsReleased) / FlashTravelMsPerPx;
        if (flashPxMovedSinceRelease < flash0MaxPos)
        {
            flash0Pos = flashPxMovedSinceRelease;
        }
        else if (flashPxMovedSinceRelease < flash0MaxPos * 2)
        {
            flash0Pos = flash0MaxPos * 2 - flashPxMovedSinceRelease;
        }

        if (flashPxMovedSinceRelease < flash1MaxPos)
        {
            flash1Pos = flashPxMovedSinceRelease;
        }
        else if (flashPxMovedSinceRelease < flash1MaxPos * 2)
        {
            flash1Pos = flash1MaxPos * 2 - flashPxMovedSinceRelease;
        }

        for (uint8_t i = 0; i < flashLength; i++)
        {
            if (flash0Pos != -1 && flash0Pos < LED::Array0::Length)
            {
                LED::Array0::HsvBuffer[flash0Pos + i].s = 255;
                LED::Array0::HsvBuffer[flash0Pos + i].v = 255;
            }

            if (flash1Pos != -1 && flash1Pos < LED::Array1::Length)
            {
                LED::Array1::HsvBuffer[flash1Pos + i].s = 255;
                LED::Array1::HsvBuffer[flash1Pos + i].v = 255;
            }
        }
    }

    hsv2rgb_rainbow(LED::Array0::HsvBuffer, LED::Array0::Buffer, LED::Array0::Length);
    hsv2rgb_rainbow(LED::Array1::HsvBuffer, LED::Array1::Buffer, LED::Array1::Length);
}
