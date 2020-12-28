#include "gates/switch.h"
#include "signal.h"

Switch::Switch()
    : Element (0, 1)
{ }

void Switch::process()
{

}

void Switch::changeOutput(State state)
{
    mOutputs.at(0)->setState(state);
}

void Switch::toggleOutput()
{
    mOutputs.at(0)->setState((mOutputs.at(0)->getVal() ^ 1));
}
