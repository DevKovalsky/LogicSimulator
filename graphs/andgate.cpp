#include "andgate.h"

AndGate::AndGate(uint32_t inputsCount)
    : Element (inputsCount, 1)
{ }

void AndGate::process()
{
    uint32_t res = 1;
    for(auto& input : mInputs)
    {
        if(input != nullptr)
            res *= input->getVal();
    }

    if(res > 0)
        mOutputs.at(0)->setState(State::HIGH);
    else
        mOutputs.at(0)->setState(State::LOW);
}

