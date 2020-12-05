#pragma once

#include <map>
#include <memory>

#include "element.h"

class AdjacencyList;

class Box : public Element
{
public:
    Box() = default;
    ~Box() = default;

    void addElement(std::shared_ptr<Element> element);
    //vector<uint> getInputsVerticesIdx

private:
    std::map<uint32_t, std::shared_ptr<Element>> mIdxToElements{};
    std::unique_ptr<AdjacencyList> mAdjacencyList{};
};
