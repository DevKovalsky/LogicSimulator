#include "adjacencylist.h"
#include "box.h"
#include "gates/orgate.h"
#include "gates/switch.h"
#include "gates/andgate.h"
#include "gates/notgate.h"

#include "Logger.h"

int main(int argc, char *argv[])
{

    Logger logger(LogLevel::INFO);
    logger.addStream(std::wcout, LogLevel::INFO);

    LOGINFO(logger, "LogicSimulator start");

    std::shared_ptr<Switch> switch1 = std::make_shared<Switch>();
    std::shared_ptr<Switch> switch2 = std::make_shared<Switch>();
    std::shared_ptr<Switch> switch3 = std::make_shared<Switch>();
    std::shared_ptr<Switch> switch4 = std::make_shared<Switch>();
    std::shared_ptr<OrGate> or1 = std::make_shared<OrGate>(2);
    std::shared_ptr<OrGate> or2 = std::make_shared<OrGate>(2);
    std::shared_ptr<AndGate> and1 = std::make_shared<AndGate>(2);
    std::shared_ptr<NotGate> not1 = std::make_shared<NotGate>();
    Box circuit{0, 0};
    circuit.addElement(switch1); // 0
    circuit.addElement(switch2); // 1
    circuit.addElement(switch3); // 2
    circuit.addElement(switch4); // 3
    circuit.addElement(or1); // 4
    circuit.addElement(or2); // 5
    circuit.addElement(and1); // 6
    circuit.addElement(not1); // 7

    //switch1->toggleOutput();
    //switch2->toggleOutput();
    //switch3->toggleOutput();
    //switch4->toggleOutput();

    //circuit.createConnectionBetweenElements(switch1->getIdx(), or1->getIdx(), 0, 0);
    circuit.createConnectionBetweenElements(switch2->getIdx(), or1->getIdx(), 1, 0);

    circuit.createConnectionBetweenElements(switch3->getIdx(), or2->getIdx(), 0, 0);
    circuit.createConnectionBetweenElements(switch4->getIdx(), or2->getIdx(), 1, 0);

    circuit.createConnectionBetweenElements(or1->getIdx(), and1->getIdx(), 0, 0);
    circuit.createConnectionBetweenElements(or2->getIdx(), and1->getIdx(), 1, 0);

    circuit.createConnectionBetweenElements(and1->getIdx(), not1->getIdx(), 0, 0);

    std::shared_ptr<Switch> subSwitch1 = std::make_shared<Switch>();
    std::shared_ptr<Switch> subSwitch2 = std::make_shared<Switch>();
    std::shared_ptr<OrGate> subOr1 = std::make_shared<OrGate>(2);
    std::shared_ptr<Box> subCircuit = std::make_shared<Box>(0, 0);

    subCircuit->addElement(subSwitch1);
    subCircuit->addElement(subSwitch2);
    subCircuit->addElement(subOr1);

    subCircuit->createConnectionBetweenElements(subSwitch1->getIdx(), subOr1->getIdx(), 0, 0);
    subCircuit->createConnectionBetweenElements(subSwitch2->getIdx(), subOr1->getIdx(), 1, 0);

    //circuit.addElement(subCircuit);
    circuit.appendCircuit(subCircuit);

    auto inIdxs = subCircuit->getInputVerticesIdx();
    auto outIdxs = subCircuit->getOutputVerticesIdx();

    auto in = subCircuit->getInputElements();
    auto out = subCircuit->getOutputElements();

    circuit.createConnectionBetweenElements(out[0]->getIdx(), or1->getIdx(), 0, 0);

    subSwitch2->changeOutput(State::HIGH);
    switch4->changeOutput(State::HIGH);

    circuit.process();

    std::string outputStr = "Output: " + std::to_string(not1->getOutput(0)->getVal());
    LOGDEBUG(logger, outputStr.c_str());
    LOGINFO(logger, "Good bye :)");

    return 0;
}
