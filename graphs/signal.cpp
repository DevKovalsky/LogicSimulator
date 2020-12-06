#include "signal.h"

void Signal::setState(State state)
{
    mState = state;
}

void Signal::setState(uint32_t val)
{
    if(val > 0)
        mState = State::HIGH;
    else
        mState = State::LOW;
}
