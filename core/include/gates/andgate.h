#pragma once

#include "element.h"

class AndGate : public Element
{
public:
    AndGate(uint32_t inputsCount);
    ~AndGate() override = default;

    void process() override;
};

