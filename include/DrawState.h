#ifndef __DRAWSTATE_H__
#define __DRAWSTATE_H__

#include <stdint.h>

// All values in miliseconds
struct DrawState {
    uint32_t tsCurrent;  // Current time
    uint32_t tsPulled;   // When the trigger was last pulled
    uint32_t tsReleased; // When the trigger was last released
    uint8_t analog;      // Where the joystick currently is
};

#endif