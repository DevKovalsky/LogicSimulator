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

    void setState(State state) { mState = state; }
    void setState(uint32_t val) { mState = State(val); }

private:
    State mState{};
};

