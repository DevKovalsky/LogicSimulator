#include "notgate.h"

NotGate::NotGate()
    : Element(1, 1)
{ }

void NotGate::process()
{
    if(mInputs.at(0) != nullptr)
    {
        if(mInputs.at(0)->getState() == State::LOW)
            mOutputs.at(0)->setState(State::HIGH);
        else
            mOutputs.at(0)->setState(State::LOW);
    }
}
