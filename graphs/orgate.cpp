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

    mOutputs.at(0)->setState(res);
}
