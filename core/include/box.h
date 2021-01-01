#pragma once

#include <map>
#include <memory>

#include "gates/element.h"

class AdjacencyList;

struct Connection
{
    uint32_t from;
    uint32_t to;
    uint32_t inputNumber;
    uint32_t outputNumber;

    Connection(uint32_t start, uint32_t end, uint32_t input, uint32_t output)
    {
        from = start;
        to = end;
        inputNumber = input;
        outputNumber = output;
    }
};

class Box : public Element
{
public:
    Box(uint32_t inputsCount, uint32_t outputsCount);
    virtual ~Box() override = default;

    void process() override;

    void addElement(std::shared_ptr<Element> element);
    void removeElement(uint32_t idx);
    void createConnectionBetweenElements(uint32_t startIdx, uint32_t endIdx, uint32_t outIdx, uint32_t inIdx);
    std::vector<uint32_t> getInputVerticesIdx();
    std::vector<uint32_t> getOutputVerticesIdx();
    std::vector<std::shared_ptr<Element>> getInputElements();
    std::vector<std::shared_ptr<Element>> getOutputElements();
    void appendCircuit(std::shared_ptr<Box> box);

private:
    std::map<uint32_t, std::shared_ptr<Element>> mIdxsToElements{};
    std::unique_ptr<AdjacencyList> mAdjacencyList{};
    std::vector<Connection> mConnections{};
};
