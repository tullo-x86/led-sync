#ifndef __DRAWSTATE_H__
#define __DRAWSTATE_H__

#include <stdint.h>

struct DrawState {
    uint32_t tsCurrent;
    uint32_t tsPulled;
    uint32_t tsReleased;
    uint8_t analog;
};

#endif