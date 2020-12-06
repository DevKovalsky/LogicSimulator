#include "adjacencylist.h"

#include <algorithm>

AdjacencyList::AdjacencyList(uint32_t vertexCount)
{
    mAdjacency.resize(vertexCount);
}

void AdjacencyList::addEdge(uint32_t startVertexIdx, uint32_t endVertexIdx)
{
    mAdjacency.at(startVertexIdx).emplace_back(endVertexIdx);
}

bool AdjacencyList::removeEdge(uint32_t startVertexIdx, uint32_t endVertexIdx)
{
    auto neighbors = mAdjacency.at(startVertexIdx);
    auto res = std::find(std::begin(neighbors), std::end(neighbors), endVertexIdx);
    if(res != std::end(neighbors))
    {
        auto dis = std::distance(neighbors.begin(), res);
        mAdjacency.at(startVertexIdx).erase(mAdjacency.at(startVertexIdx).begin() + dis);
        return true;
    }

    return false;
}

uint32_t AdjacencyList::addVertex()
{
    uint32_t newVertexIdx = static_cast<uint32_t>(mAdjacency.size());
    mAdjacency.emplace_back(newVertexIdx);
    mAdjacency.at(newVertexIdx).resize(0); // ?
    return newVertexIdx;
}

bool AdjacencyList::removeVertex(uint32_t vertexIdx) // vector idx shift :(, przy usunieciu->izolowany wierzcholek i idx do wolnej puli, najpierw z puli, nastepnie kolejny
{
    auto res = mAdjacency.erase(mAdjacency.begin() + vertexIdx);
    if(res != std::end(mAdjacency))
        return true;

    return false;
}

uint32_t AdjacencyList::getInDegree(uint32_t vertexIdx)
{
    uint32_t counter{};
    for(auto& vertices : mAdjacency)
    {
        for(auto& vertex : vertices)
        {
            if(vertex == vertexIdx)
                counter++;
        }
    }
    return counter;
}

uint32_t AdjacencyList::getOutDegree(uint32_t vertexIdx)
{
    return static_cast<uint32_t>(mAdjacency.at(vertexIdx).size());
}

bool AdjacencyList::isIsolated(uint32_t vertexIdx)
{
    return mAdjacency.at(vertexIdx).empty();
}

std::vector<uint32_t> AdjacencyList::getAllIsolatedVertices()
{
    std::vector<uint32_t> isolated{};
    for(uint32_t i = 0; i < mAdjacency.size(); ++i) //dla iteratorów
    {
        if(isIsolated(i))
            isolated.emplace_back(i);
    }
    return isolated;
}

uint32_t AdjacencyList::getVerticesCount()
{
    return static_cast<uint32_t>(mAdjacency.size());
}

std::vector<uint32_t> AdjacencyList::getVertexNeighbors(uint32_t vertexIdx) //sąsiedzi wierzchołka vi ->
{
    return mAdjacency.at(vertexIdx);
}

std::vector<uint32_t> AdjacencyList::getVerticesWhereIdxIsNeighbor(uint32_t vertexIdx) //Wierzchołki, dla których vi  jest sąsiadem <-
{
    std::vector<uint32_t> neighbors{};
    for(uint32_t i = 0; i < mAdjacency.size(); ++i)
    {
        for(auto& vertex : mAdjacency.at(i))
        {
            if(vertex == vertexIdx)
            {
                neighbors.emplace_back(i);
                break; // ?
            }
        }
    }
    return neighbors;
}

bool AdjacencyList::isLoop(uint32_t vertexIdx)
{
    for(auto& vertex : mAdjacency.at(vertexIdx))
    {
        if(vertex == vertexIdx)
            return true;
    }
    return false;
}

bool AdjacencyList::isBidirectionalEdge(uint32_t startVertexIdx, uint32_t endVertexIdx)
{
    if(startVertexIdx == endVertexIdx)
        return false;

    uint32_t counter{};

    for(auto& vertex : mAdjacency.at(startVertexIdx))
    {
        if(vertex == endVertexIdx)
        {
            counter++;
            break;
        }
    }
    for(auto& vertex : mAdjacency.at(endVertexIdx))
    {
        if(vertex == startVertexIdx)
        {
            counter++;
            break;
        }
    }

    if(counter >= 2)
        return true;

    return false;
}

std::vector<std::pair<uint32_t, uint32_t>> AdjacencyList::getAllBidirectionalEdges()
{
    std::vector<std::pair<uint32_t, uint32_t>> bidirectionalEdges{};
    for (uint32_t i = 0; i < mAdjacency.size(); ++i)
    {
        for (uint32_t j = 0; j < mAdjacency.at(i).size(); ++j)
        {
            if(isBidirectionalEdge(i, mAdjacency.at(i).at(j)))
                bidirectionalEdges.emplace_back(std::pair<uint32_t, uint32_t>{i, mAdjacency.at(i).at(j)});
        }
    }
    return bidirectionalEdges;
}

std::vector<uint32_t> AdjacencyList::getAllLoops()
{
    std::vector<uint32_t> loops{};
    for(uint32_t i = 0; i < mAdjacency.size(); ++i)
    {
        if(isLoop(i))
            loops.emplace_back(i);
    }
    return loops;
}

std::vector<uint32_t> AdjacencyList::DFS(uint32_t startVertexIdx)
{
    std::vector<uint32_t> dfs{};
    std::vector<bool> visited{};
    visited.resize(mAdjacency.size());
    recursiveDFS(startVertexIdx, dfs, visited);
    return dfs;
}

void AdjacencyList::recursiveDFS(uint32_t idx, std::vector<uint32_t>& dfs, std::vector<bool>& visited)
{
    if(visited.at(idx))
        return;

    visited.at(idx) = true;
    dfs.emplace_back(idx); // "process"
    auto vertices = mAdjacency.at(idx);
    for(uint32_t j = 0; j < vertices.size(); ++j)
    {
        if(!visited.at(vertices.at(j)))
            recursiveDFS(vertices.at(j), dfs, visited);
    }
}

std::stack<uint32_t> AdjacencyList::topologicalSort()
{
    std::stack<uint32_t> sorted{};
    std::vector<bool> visited{}; //uint8_t (char)??
    visited.resize(mAdjacency.size());

    for(uint32_t i = 0; i < mAdjacency.size(); ++i)
    {
        if(visited.at(i) == false)
            topologicalSortRecursive(i, sorted, visited);
    }
    return sorted;
}

void AdjacencyList::topologicalSortRecursive(uint32_t idx, std::stack<uint32_t>& sorted, std::vector<bool>& visited)
{
    visited.at(idx) = true;

    for(auto& el : mAdjacency.at(idx))
    {
        if(visited.at(el) == false)
            topologicalSortRecursive(el, sorted, visited);
    }

    sorted.push(idx);
}

void AdjacencyList::show()
{
    for(uint32_t i = 0; i < mAdjacency.size(); ++i)
    {
        std::cout << i << ": ";
        for(uint32_t j = 0; j < mAdjacency.at(i).size(); ++j)
        {
            std::cout << mAdjacency.at(i).at(j) << " ";
        }
        std::cout << std::endl;
    }
}
