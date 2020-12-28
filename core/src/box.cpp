#include "box.h"

#include "adjacencylist.h"

Box::Box(uint32_t inputsCount, uint32_t outputsCount)
    : Element(inputsCount, outputsCount)
{
    mAdjacencyList = std::make_unique<AdjacencyList>(0);
    mAdjacencyList->clear();
}

void Box::process()
{
    mAdjacencyList->show();
    auto elementsOrder = mAdjacencyList->topologicalSort();
    while (elementsOrder.empty() == false)
    {
        auto top = elementsOrder.top();
        if(mIdxsToElements.count(top) == 0)
            return;
        mIdxsToElements.at(top)->process();
        elementsOrder.pop();
    }
}

void Box::addElement(std::shared_ptr<Element> element)
{
    mAdjacencyList->addVertex(element->getIdx());
    mIdxsToElements[element->getIdx()] = element;
}

void Box::removeElement(uint32_t idx)
{
    mIdxsToElements.erase(idx);
    mAdjacencyList->removeVertex(idx);
}

void Box::createConnectionBetweenElements(uint32_t startIdx, uint32_t endIdx, uint32_t inIdx, uint32_t outIdx)
{
    mAdjacencyList->addEdge(startIdx, endIdx);
    mIdxsToElements.at(endIdx)->setInput(inIdx, mIdxsToElements.at(startIdx)->getOutput(outIdx));
}

std::vector<uint32_t> Box::getInputVerticesIdx()
{
    return mAdjacencyList->getInputs();
}

std::vector<uint32_t> Box::getOutputVerticesIdx()
{
    return mAdjacencyList->getOutputs();
}

std::vector<std::shared_ptr<Element>> Box::getInputElements()
{
    std::vector<std::shared_ptr<Element>> elements{};
    auto idxs = mAdjacencyList->getInputs();
    for(auto& idx : idxs)
    {
        elements.emplace_back(mIdxsToElements[idx]);
    }
    return elements;
}

std::vector<std::shared_ptr<Element>> Box::getOutputElements()
{
    std::vector<std::shared_ptr<Element>> elements{};
    auto idxs = mAdjacencyList->getOutputs();
    for(auto& idx : idxs)
    {
        elements.emplace_back(mIdxsToElements[idx]);
    }
    return elements;
}

void Box::appendCircuit(std::shared_ptr<Box> box)
{
    for(auto& pair : box->mIdxsToElements)
    {
        auto idx = pair.first;
        if(mIdxsToElements.find(idx) != mIdxsToElements.end() || mAdjacencyList->hasIdx(idx)) // or czy and??
        {
            return;
        }
        mIdxsToElements[idx] = pair.second;
        addElement(pair.second);
        // add some log
    }
}
