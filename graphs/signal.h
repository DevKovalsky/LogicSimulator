#pragma once

#include <stdint.h>

enum class State
{
    LOW,
    HIGH
};

class Signal
{
public:
    Signal() = default;
    ~Signal() = default;

    State getState() { return mState; }
    uint32_t getVal() { return static_cast<uint32_t>(mState); }

    inline void setState(State state);
    inline void setState(uint32_t val);

private:
    State mState{};
};

