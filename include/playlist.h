
#ifndef PLAYLIST_H
#define PLAYLIST_H

#include "FastLED.h"
#include <lib8tion.h>

// Forward declaration
template<typename... TPatterns>
class PlaylistImpl
{
public:
    void dispatchReset(uint8_t index);
    void dispatchUpdate(uint8_t index, uint16_t deltaTime);
    void dispatchDraw(uint8_t index);
};



// Specialisation of template for the empty case (always the tail)
template<>
class PlaylistImpl<> {

public:
    void dispatchReset(uint8_t index) { /* Should never be called */ }
    void dispatchUpdate(uint8_t index, uint16_t deltaTime) { /* Should never be called */ }
    void dispatchDraw(uint8_t index) { /* Should never be called */ }
};



// Specialisation of template for every instance in the chain
// THIS MUST NOT CONTAIN MEMBERS WHICH ARE NOT PATTERN INSTANCES,
// as they will SHARE MEMORY WITH and BE CLOBBERED BY the
// pattern instance members.
template<typename THeadPattern, typename... TRemainingPatterns>
class PlaylistImpl<THeadPattern, TRemainingPatterns...> {
    union {
        THeadPattern head;
        PlaylistImpl<TRemainingPatterns...> rest;
    };

public:
    PlaylistImpl() {
        dispatchReset(0);
    }

    void dispatchReset(uint8_t index)
    {
        if (index <= 0)
        {
            head.reset();
        }
        else
        {
            rest.dispatchReset(index - 1);
        }
    }

    void dispatchUpdate(uint8_t index, uint16_t deltaTime)
    {
        if (index <= 0)
        {
            head.update(deltaTime);
        }
        else
        {
            rest.dispatchUpdate(index - 1, deltaTime);
        }
    }

    void dispatchDraw(uint8_t index)
    {
        if (index <= 0)
        {
            head.draw();
        }
        else
        {
            rest.dispatchDraw(index - 1);
        }
    }
};

// This is the the interface that the "user code" should see.
template <typename... TPatterns>
class Playlist {

    static constexpr uint8_t PatternCount = sizeof...(TPatterns);
    PlaylistImpl<TPatterns...> _playlistImpl;

    uint8_t _currentPatternIndex;

public:
    Playlist() {
        _currentPatternIndex = 0;
        _playlistImpl.dispatchReset(_currentPatternIndex);
    }

    void goToIndex(uint8_t patternIndex)
    {
        _currentPatternIndex = mod8(patternIndex, PatternCount);
        _playlistImpl.dispatchReset(_currentPatternIndex);
    }

    void advanceToNext()
    {
        _currentPatternIndex = addmod8(_currentPatternIndex, 1, PatternCount);
        _playlistImpl.dispatchReset(_currentPatternIndex);
    }

    void dispatchUpdate(uint16_t deltaTime)
    {
        _playlistImpl.dispatchUpdate(_currentPatternIndex, deltaTime);
    }

    void dispatchDraw()
    {
        _playlistImpl.dispatchDraw(_currentPatternIndex);
    }

    uint8_t getCurrentIndex() { return _currentPatternIndex; }
};


#endif //PLAYLIST_H
