#include "element.h"

Element::Element(uint32_t inputsCount, uint32_t outputsCount)
{
    mInputs.resize(inputsCount);
    mOutputs.resize(outputsCount);
}

void Element::setOutput(uint32_t outIdx, std::shared_ptr<Signal> signal)
{
    mOutputs.at(outIdx) = signal;
}

std::shared_ptr<Signal> Element::getOutput(uint32_t outIdx)
{
    if(outIdx >= mOutputs.size())
        return nullptr;

    return mOutputs.at(outIdx);
}

std::shared_ptr<Signal> Element::getInput(uint32_t inIdx)
{
    if(inIdx >= mInputs.size())
        return nullptr;

    return mInputs.at(inIdx);
}

uint32_t Element::getIdx()
{
    return idx;
}
