#pragma once

#include "element.h"

class OrGate : public Element
{
public:
    OrGate(uint32_t inputsCount);
    ~OrGate() override = default;

    void process() override;
};

