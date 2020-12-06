#pragma once

#include "element.h"

class XorGate : public Element
{
public:
    XorGate(uint32_t inputsCount);
    ~XorGate() override = default;

    void process() override;
};

