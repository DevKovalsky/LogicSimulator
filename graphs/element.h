#pragma once

#include <string>
#include <vector>
#include <memory>

class Element
{
public:
    Element(uint32_t inputsCount, uint32_t outputsCount);
    virtual ~Element() = default;

    virtual void process() = 0;

    void setInput(uint32_t inIdx, std::shared_ptr<Signal> signal);
    void setOutput(uint32_t outIdx, std::shared_ptr<Signal> signal);
    std::shared_ptr<Signal> getOutput(uint32_t outIdx);
    std::shared_ptr<Signal> getInput(uint32_t inIdx);
    uint32_t getIdx();

protected:
    std::string name{};
    static uint32_t staticIndex;
    uint32_t idx{};
    std::vector<std::shared_ptr<Signal>> mInputs{};
    std::vector<std::shared_ptr<Signal>> mOutputs{};
};

