#include "adjacencylist.h"

#include <algorithm>

AdjacencyList::AdjacencyList(uint32_t vertexCount)
{
}

void AdjacencyList::addEdge(uint32_t startVertexIdx, uint32_t endVertexIdx)
{
    try
    {
        mAdjacency.at(startVertexIdx).emplace_back(endVertexIdx);
    }
    catch (std::out_of_range& ex)
    {
        std::cout << __FUNCTION__ << ":" << __LINE__ << " Out of range. start: " << startVertexIdx << " end: " << endVertexIdx << std::endl;
    }

}

bool AdjacencyList::removeEdge(uint32_t startVertexIdx, uint32_t endVertexIdx)
{
    try
    {
        auto neighbors = mAdjacency.at(startVertexIdx);
        auto res = std::find(std::begin(neighbors), std::end(neighbors), endVertexIdx);
        if(res != std::end(neighbors))
        {
            auto dis = std::distance(neighbors.begin(), res);
            mAdjacency.at(startVertexIdx).erase(mAdjacency.at(startVertexIdx).begin() + dis);
            return true;
        }
    }
    catch (std::out_of_range& ex)
    {
        std::cout << __FUNCTION__ << ":" << __LINE__ << " Out of range. start: " << startVertexIdx << " end: " << endVertexIdx << std::endl;
    }

    return false;
}

uint32_t AdjacencyList::addVertex()
{
    return 0;
}

void AdjacencyList::addVertex(uint32_t idx)
{
    mAdjacency[idx] = std::vector<uint32_t>{};
}

bool AdjacencyList::removeVertex(uint32_t vertexIdx) // vector idx shift :(, przy usunieciu->izolowany wierzcholek i idx do wolnej puli, najpierw z puli, nastepnie kolejny
{
    mAdjacency.erase(vertexIdx);
    return true;
}

uint32_t AdjacencyList::getInDegree(uint32_t vertexIdx)
{
    uint32_t counter{};
    for(auto& row : mAdjacency)
    {
        for(auto& vertex : row.second)
        {
            if(vertex == vertexIdx)
                counter++;
        }
    }
    return counter;
}

uint32_t AdjacencyList::getOutDegree(uint32_t vertexIdx)
{
    try
    {
        return mAdjacency.at(vertexIdx).size();
    }
    catch (std::out_of_range& ex)
    {
        std::cout << __FUNCTION__<< ":" << __LINE__ << " Out of range. vertexId: " << vertexIdx << std::endl;
        return 0;
    }
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
    try
    {
        return mAdjacency.at(vertexIdx);
    }
    catch (std::out_of_range& ex)
    {
        std::cout << __FUNCTION__ << ":"  << __LINE__ << " Out of range. vertexId: " << vertexIdx << std::endl;
        return {};
    }
}

std::vector<uint32_t> AdjacencyList::getVerticesWhereIdxIsNeighbor(uint32_t vertexIdx) //Wierzchołki, dla których vi  jest sąsiadem <-
{
    std::vector<uint32_t> neighbors{};
    try
    {
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
    }
    catch (std::out_of_range& ex)
    {
        std::cout << __FUNCTION__ << ":"  << __LINE__ << " Out of range. vertexId: " << vertexIdx << std::endl;
        return {};
    }

    return neighbors;
}

bool AdjacencyList::isLoop(uint32_t vertexIdx)
{
    try
    {
        for(auto& vertex : mAdjacency.at(vertexIdx))
        {
            if(vertex == vertexIdx)
                return true;
        }
    }
    catch (std::out_of_range& ex)
    {
        std::cout << __FUNCTION__ << ":"  << __LINE__ << " Out of range. vertexId: " << vertexIdx << std::endl;
        return {};
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
    try
    {
        std::map<uint32_t, bool> visited{};

        for(auto& row : mAdjacency)
            visited[row.first] = false;

        for(auto& row : mAdjacency)
        {
            if(visited.at(row.first) == false)
                topologicalSortRecursive(row.first, sorted, visited);
        }
    }
    catch (std::out_of_range& ex)
    {
        std::cout << __FUNCTION__ << ":"  << __LINE__ << " Out of range." << std::endl;
        return {};
    }

    return sorted;
}

std::vector<uint32_t> AdjacencyList::getInputs()
{
    std::vector<uint32_t> inputs{};
    for(auto& row : mAdjacency)
    {
        auto idx = row.first;
        if(getInDegree(idx) == 0 && getOutDegree(idx) > 0)
            inputs.emplace_back(idx);
    }
    return inputs;
}

std::vector<uint32_t> AdjacencyList::getOutputs()
{
    std::vector<uint32_t> outputs{};
    for(auto& row : mAdjacency)
    {
        auto idx = row.first;
        if(getInDegree(idx) > 0 && getOutDegree(idx) == 0)
            outputs.emplace_back(idx);
    }
    return outputs;
}

void AdjacencyList::topologicalSortRecursive(uint32_t idx, std::stack<uint32_t>& sorted, std::map<uint32_t, bool>& visited)
{
    try
    {
        visited.at(idx) = true;

        for(auto& el : mAdjacency.at(idx))
        {
            if(visited.at(el) == false)
                topologicalSortRecursive(el, sorted, visited);
        }

        sorted.push(idx);
    }
    catch (std::out_of_range& ex)
    {
        std::cout << __FUNCTION__ << ":"  << __LINE__ << " Out of range." << std::endl;
    }
}

void AdjacencyList::show()
{
    for(auto& row : mAdjacency)
    {
        std::cout << row.first << ": ";
        for(auto& vertex : row.second)
        {
             std::cout << vertex << " ";
        }
        std::cout << std::endl;
    }
}

void AdjacencyList::clear()
{
    mAdjacency.clear();
}

bool AdjacencyList::hasIdx(uint32_t idx)
{
    return mAdjacency.find(idx) != mAdjacency.end();
}
