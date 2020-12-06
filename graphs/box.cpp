#include "box.h"

#include "adjacencylist.h"

Box::Box(uint32_t inputsCount, uint32_t outputsCount)
    : Element(inputsCount, outputsCount)
{
    mAdjacencyList = std::make_unique<AdjacencyList>(0);
}

void Box::process()
{
    mAdjacencyList->show();
    auto elementsOrder = mAdjacencyList->topologicalSort();
    while (elementsOrder.empty() == false)
    {
        auto top = elementsOrder.top();
        mIdxsToElements.at(top)->process();
        elementsOrder.pop();
    }
}

void Box::addElement(std::shared_ptr<Element> element)
{
    mAdjacencyList->addVertex();
    mIdxsToElements[element->getIdx()] = element;
    //mAdjacency.addVertex(element->getIdx()); //ale to tylko vector
}

void Box::removeElement(uint32_t idx)
{
    mIdxsToElements.erase(idx);
    //remove from adjacency list
}

void Box::createConnectionBetweenElements(uint32_t startIdx, uint32_t endIdx, uint32_t inIdx, uint32_t outIdx)
{
    mAdjacencyList->addEdge(startIdx, endIdx);
    mIdxsToElements.at(endIdx)->setInput(inIdx, mIdxsToElements.at(startIdx)->getOutput(outIdx));
}
