#pragma once

#include <map>
#include <memory>

#include "element.h"

class AdjacencyList;

class Box : public Element
{
public:
    Box(uint32_t inputsCount, uint32_t outputsCount);
    virtual ~Box() override = default;

    void process() override;

    void addElement(std::shared_ptr<Element> element);
    void removeElement(uint32_t idx);
    void createConnectionBetweenElements(uint32_t startIdx, uint32_t endIdx, uint32_t outIdx, uint32_t inIdx);
    //vector<uint32_t> getInputsVerticesIdx

private:
    std::map<uint32_t, std::shared_ptr<Element>> mIdxsToElements{};
    std::unique_ptr<AdjacencyList> mAdjacencyList;
};
