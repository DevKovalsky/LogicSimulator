#include "orgate.h"

OrGate::OrGate(uint32_t inputsCount)
    : Element (inputsCount, 1)
{ }

void OrGate::process()
{
    uint32_t res{};
    for(auto& input : mInputs)
    {
        if(input != nullptr)
            res += input->getVal();
    }

    if(res > 0)
        mOutputs.at(0)->setState(State::HIGH);
    else
        mOutputs.at(0)->setState(State::LOW);
}
