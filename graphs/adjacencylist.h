#pragma once

#include <iostream>

#include "igraph.h"

class AdjacencyList : public IGraph
{
public:
    AdjacencyList(uint32_t vertexCount);
    ~AdjacencyList() override = default;

    void addEdge(uint32_t startVertexIdx, uint32_t endVertexIdx) override;
    bool removeEdge(uint32_t startVertexIdx, uint32_t endVertexIdx) override;
    uint32_t addVertex() override;
    bool removeVertex(uint32_t vertexIdx) override;
    std::vector<uint32_t> getVertexNeighbors(uint32_t vertexIdx) override;
    std::vector<uint32_t> getVerticesWhereIdxIsNeighbor(uint32_t vertexIdx) override;
    uint32_t getVerticesCount() override;
    bool isLoop(uint32_t vertexIdx) override;
    bool isIsolated(uint32_t vertexIdx) override;
    bool isBidirectionalEdge(uint32_t startVertexIdx, uint32_t endVertexIdx) override;
    uint32_t getInDegree(uint32_t vertexIdx) override;
    uint32_t getOutDegree(uint32_t vertexIdx) override;
    std::vector<uint32_t> getAllIsolatedVertices() override;
    std::vector<std::pair<uint32_t, uint32_t> > getAllBidirectionalEdges() override;
    std::vector<uint32_t> getAllLoops() override;
    std::vector<uint32_t> DFS(uint32_t startVertexIdx) override;
    std::stack<uint32_t> topologicalSort() override;
    void show() override;

protected:
    void recursiveDFS(uint32_t idx, std::vector<uint32_t> &dfs, std::vector<bool> &visited) override;
    void topologicalSortRecursive(uint32_t idx, std::stack<uint32_t> &sorted, std::vector<bool> &visited) override;

private:
    std::vector<std::vector<uint32_t>> mAdjacency;
};
