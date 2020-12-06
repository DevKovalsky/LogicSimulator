#pragma once

#include "element.h"

class Switch  : public Element
{
public:
    Switch();
    ~Switch() override = default;

    void process() override;

    void changeOutput(State state);
    void toggleOutput();
};

