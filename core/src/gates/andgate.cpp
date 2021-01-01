#include "gates/andgate.h"
#include "signal.h"

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

    mOutputs.at(0)->setState(res);

    std::string msg = "And idx = " + std::to_string(getIdx()) + " output value = " + std::to_string(res);
    LOGINFO(logger, msg.c_str());
}

