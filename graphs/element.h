#pragma once

#include <string>

class Element //->Gate->OrGate... IO->Switch | ->Button... Box
{
public:
    Element() = default;
    ~Element() = default;

    //void process

    //getOut

private:
    std::string name{};
    //inputs vector<shared<Signal>> ??
    //outputs vector<shared<Signal>>
};

