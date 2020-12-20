#pragma once

#include <iomanip>
#include <vector>
#include <stack>

class IGraph
{
public:
    virtual ~IGraph() = default;
    virtual void addEdge(uint32_t startVertexIdx, uint32_t endVertexIdx) = 0;
    virtual bool removeEdge(uint32_t startVertexIdx, uint32_t endVertexIdx) = 0;
    virtual uint32_t addVertex() = 0;
    virtual bool removeVertex(uint32_t vertexIdx) = 0;
    virtual std::vector<uint32_t> getVertexNeighbors(uint32_t vertexIdx) = 0;
    virtual std::vector<uint32_t> getVerticesWhereIdxIsNeighbor(uint32_t vertexIdx) = 0;
    virtual uint32_t getVerticesCount() = 0;
    virtual bool isLoop(uint32_t vertexIdx) = 0;
    virtual bool isIsolated(uint32_t vertexIdx) = 0;
    virtual bool isBidirectionalEdge(uint32_t startVertexIdx, uint32_t endVertexIdx) = 0;
    virtual uint32_t getInDegree(uint32_t vertexIdx) = 0;
    virtual uint32_t getOutDegree(uint32_t vertexIdx) = 0;
    virtual std::vector<uint32_t> getAllIsolatedVertices() = 0;
    virtual std::vector<std::pair<uint32_t, uint32_t>> getAllBidirectionalEdges() = 0;
    virtual std::vector<uint32_t> getAllLoops() = 0;
    virtual std::vector<uint32_t> DFS(uint32_t startVertexIdx) = 0;
    virtual std::stack<uint32_t> topologicalSort() = 0;
    virtual std::vector<uint32_t> getInputs() = 0;
    virtual std::vector<uint32_t> getOutputs() = 0;
    virtual void show() = 0;

protected:
      virtual void recursiveDFS(uint32_t idx, std::vector<uint32_t>& dfs, std::vector<bool>& visited) = 0;
      virtual void topologicalSortRecursive(uint32_t idx, std::stack<uint32_t>& sorted, std::vector<bool>& visited) = 0;
};
