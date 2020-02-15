#ifndef MATHUTIL_H
#define MATHUTIL_H

#include <lib8tion.h>

// Returns an unsigned fixed-point value representing a fraction
// between 0 and 0.99609375 (=255/256), equivalent to (dividend/divisor)
// multiplied by 256.
//
// i.e. fractOf(100, 200) will return 128,
//      fractOf( 32, 128) will return 64
inline fract8 fractOf(uint16_t dividend, uint16_t divisor) {
    constexpr uint16_t u16_255 = 0xff;
    return (dividend * u16_255) / divisor;
}

inline fract8 fractOf(uint32_t dividend, uint32_t divisor) {
    constexpr uint32_t u32_255 = 0xff;
    return (dividend * u32_255) / divisor;
}

#endif