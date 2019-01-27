#ifndef MATHUTIL_H
#define MATHUTIL_H

#include <lib8tion.h>

inline fract8 fractOf(uint16_t dividend, uint16_t divisor) {
    constexpr uint16_t u16_255 = 0xff;
    return (dividend * u16_255) / divisor;
}

inline fract8 fractOf(uint32_t dividend, uint32_t divisor) {
    constexpr uint32_t u32_255 = 0xff;
    return (dividend * u32_255) / divisor;
}

#endif