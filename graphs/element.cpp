#include "element.h"

uint32_t Element::staticIndex = 0;

Element::Element(uint32_t inputsCount, uint32_t outputsCount)
{
    mInputs.resize(inputsCount);
    mOutputs.resize(outputsCount);
    idx = staticIndex++;
    for(auto& out : mOutputs)
        out = std::make_shared<Signal>();
}

void Element::setInput(uint32_t inIdx, std::shared_ptr<Signal> signal)
{
    mInputs.at(inIdx) = signal;
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
