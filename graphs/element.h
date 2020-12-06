#pragma once

#include <string>
#include <vector>
#include <memory>

class Element //->Gate->OrGate... IO->Switch | ->Button... Box
{
public:
    Element(uint32_t inputsCount, uint32_t outputsCount);
    virtual ~Element() = default;

    virtual void process() = 0;

    void setOutput(uint32_t outIdx, std::shared_ptr<Signal> signal);
    std::shared_ptr<Signal> getOutput(uint32_t outIdx);
    std::shared_ptr<Signal> getInput(uint32_t inIdx);
    uint32_t getIdx();

private:
    std::string name{};
    uint32_t idx{};
    std::vector<std::shared_ptr<Signal>> mInputs{};
    std::vector<std::shared_ptr<Signal>> mOutputs{};
};

