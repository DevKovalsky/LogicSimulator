#pragma once

#include "element.h"

class NotGate : public Element
{
public:
    NotGate();
    ~NotGate() override = default;

    void process() override;
};

