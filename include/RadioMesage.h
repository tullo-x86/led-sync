/*
 * RadioMessage.h
 *
 *  Created on: 15 Jan 2015
 *      Author: tully
 */

#pragma once

#include <stdint.h>
#include <stddef.h>

// Forward-declare for inner reference
union RadioMessage;

union RadioMessage
{
    struct
    {
        uint8_t idxPattern;
        uint32_t tsPulled;
        uint32_t tsReleased;
        uint32_t tsNow;
        uint32_t tScale;
        uint8_t analog;
    };

    uint8_t raw[sizeof(uint32_t) * 4 + sizeof(uint8_t) * 2];

    static constexpr size_t Size() { return sizeof(RadioMessage); }
};

