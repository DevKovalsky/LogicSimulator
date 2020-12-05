#include <QCoreApplication>

#include "adjacencylist.h"

//#include <iostream>
//#include <array>
//#include <iomanip>
//#include <string>
//#include <stack>

//class AdjacencyMatrix
//{
//public:
//    AdjacencyMatrix(uint32_t vertexCount) //make direct and indirect
//    {
//        mVertexCount = vertexCount;
//        mMatrix.resize(vertexCount);
//        for(auto& el : mMatrix)
//            el.resize(vertexCount);
//    }

//    void setEdge(uint32_t startVertexIdx, uint32_t endVertexIdx)
//    {
//        mMatrix.at(startVertexIdx).at(endVertexIdx) = 1;
//    }

//    void show()
//    {
//        std::cout << "   ";
//        for(uint32_t i = 0; i < mVertexCount; ++i)
//            std::cout << std::setw (3) << i;

//        std::cout << std::endl;
//        for(uint32_t i = 0; i < mVertexCount; ++i)
//        {
//            std::cout << std::setw(3) << i;
//            for(uint32_t j = 0; j < mVertexCount; ++j)
//                std::cout << std::setw(3) << std::to_string(mMatrix.at(i).at(j));
//            std::cout << std::endl;
//        }
//    }

//    std::vector<uint32_t> getVertexNeighbors(uint32_t vertexIdx) //sąsiedzi wierzchołka vi ->
//    {
//        std::vector<uint32_t> neighbors{};
//        for(uint32_t i = 0; i < mVertexCount; ++i)
//            if(mMatrix.at(vertexIdx).at(i) == 1)
//                neighbors.emplace_back(i);
//        return neighbors;
//    }

//    std::vector<uint32_t> getVerticesWhereIdxIsNeighbor(uint32_t vertexIdx) //Wierzchołki, dla których vi  jest sąsiadem <-
//    {
//        std::vector<uint32_t> neighbors{};
//        for(uint32_t i = 0; i < mVertexCount; ++i)
//            if(mMatrix.at(i).at(vertexIdx) == 1)
//                neighbors.emplace_back(i);
//        return neighbors;
//    }

//    bool isLoop(uint32_t vertexIdx)
//    {
//        return mMatrix.at(vertexIdx).at(vertexIdx) == 1;
//    }

//    bool isIsolated(uint32_t vertexIdx)
//    {
//        uint32_t counter{};
//        for (uint32_t i = 0; i < mVertexCount; ++i)
//            counter += mMatrix.at(vertexIdx).at(i);
//        for (uint32_t i = 0; i < mVertexCount; ++i)
//            counter += mMatrix.at(i).at(vertexIdx);
//        return counter == 0;
//    }

//    bool isBidirectionalEdge(uint32_t startVertexIdx, uint32_t endVertexIdx) //the same edges as 1 3 | 3 1
//    {
//        return startVertexIdx != endVertexIdx
//                && mMatrix.at(startVertexIdx).at(endVertexIdx) == 1 && mMatrix.at(endVertexIdx).at(startVertexIdx) == 1;
//    }

//    uint32_t getInDegree(uint32_t vertexIdx)
//    {
//        uint32_t counter{};
//        for (uint32_t i = 0; i < mVertexCount; ++i)
//            counter += mMatrix.at(i).at(vertexIdx);
//        return counter;
//    }

//    uint32_t getOutDegree(uint32_t vertexIdx)
//    {
//        uint32_t counter{};
//        for (uint32_t i = 0; i < mVertexCount; ++i)
//            counter += mMatrix.at(vertexIdx).at(i);
//        return counter;
//    }

//    std::vector<uint32_t> getAllIsolatedVertices()
//    {
//        std::vector<uint32_t> isolatedVertices{};
//        for (uint32_t i = 0; i < mVertexCount; ++i)
//        {
//            if(isIsolated(i))
//                isolatedVertices.emplace_back(i);
//        }
//        return isolatedVertices;
//    }

//    std::vector<std::pair<uint32_t, uint32_t>> getAllBidirectionalEdges()
//    {
//        std::vector<std::pair<uint32_t, uint32_t>> bidirectionalEdges{};
//        for (uint32_t i = 0; i < mVertexCount; ++i)
//        {
//            for (uint32_t j = 0; j < mVertexCount; ++j)
//            {
//                if(isBidirectionalEdge(i, j))
//                    bidirectionalEdges.emplace_back(std::pair<uint32_t, uint32_t>{i, j});
//            }
//        }
//        return bidirectionalEdges;
//    }

//private:
//    std::vector<std::vector<uint8_t>> mMatrix{};
//    uint32_t mVertexCount{};
//};

//class AdjacencyList
//{
//public:
//    AdjacencyList(uint32_t vertexCount)
//    {
//        mAdjacency.resize(vertexCount);
//    }

//    void addEdge(uint32_t startVertexIdx, uint32_t endVertexIdx)
//    {
//        mAdjacency.at(startVertexIdx).emplace_back(endVertexIdx);
//    }

//    uint32_t getInDegree(uint32_t vertexIdx)
//    {
//        uint32_t counter{};
//        for(auto& vertices : mAdjacency)
//        {
//            for(auto& vertex : vertices)
//            {
//                if(vertex == vertexIdx)
//                    counter++;
//            }
//        }
//        return counter;
//    }

//    uint32_t getOutDegree(uint32_t vertexIdx)
//    {
//        return static_cast<uint32_t>(mAdjacency.at(vertexIdx).size());
//    }

//    bool isIsolated(uint32_t vertexIdx)
//    {
//        return mAdjacency.at(vertexIdx).empty();
//    }

//    std::vector<uint32_t> getAllIsolatedVertices()
//    {
//        std::vector<uint32_t> isolated{};
//        for(uint32_t i = 0; i < mAdjacency.size(); ++i)
//        {
//            if(isIsolated(i))
//                isolated.emplace_back(i);
//        }
//        return isolated;
//    }

//    uint32_t getVerticesCount()
//    {
//        return static_cast<uint32_t>(mAdjacency.size());
//    }

//    std::vector<uint32_t> getVertexNeighbors(uint32_t vertexIdx) //sąsiedzi wierzchołka vi ->
//    {
//        return mAdjacency.at(vertexIdx);
//    }

//    std::vector<uint32_t> getVerticesWhereIdxIsNeighbor(uint32_t vertexIdx) //Wierzchołki, dla których vi  jest sąsiadem <-
//    {
//        std::vector<uint32_t> neighbors{};
//        for(uint32_t i = 0; i < mAdjacency.size(); ++i)
//        {
//            for(auto& vertex : mAdjacency.at(i))
//            {
//                if(vertex == vertexIdx)
//                {
//                    neighbors.emplace_back(i);
//                    break; // ?
//                }
//            }
//        }
//        return neighbors;
//    }

//    bool isLoop(uint32_t vertexIdx)
//    {
//        for(auto& vertex : mAdjacency.at(vertexIdx))
//        {
//            if(vertex == vertexIdx)
//                return true;
//        }
//        return false;
//    }

//    bool isBidirectionalEdge(uint32_t startVertexIdx, uint32_t endVertexIdx) //the same edges as 1 3 | 3 1
//    {
//        if(startVertexIdx == endVertexIdx)
//            return false;

//        uint32_t counter{};

//        for(auto& vertex : mAdjacency.at(startVertexIdx))
//        {
//            if(vertex == endVertexIdx)
//            {
//                counter++;
//                break;
//            }
//        }
//        for(auto& vertex : mAdjacency.at(endVertexIdx))
//        {
//            if(vertex == startVertexIdx)
//            {
//                counter++;
//                break;
//            }
//        }

//        if(counter >= 2)
//            return true;

//        return false;
//    }

//    std::vector<std::pair<uint32_t, uint32_t>> getAllBidirectionalEdges()
//    {
//        std::vector<std::pair<uint32_t, uint32_t>> bidirectionalEdges{};
//        for (uint32_t i = 0; i < mAdjacency.size(); ++i)
//        {
//            for (uint32_t j = 0; j < mAdjacency.at(i).size(); ++j)
//            {
//                if(isBidirectionalEdge(i, mAdjacency.at(i).at(j)))
//                    bidirectionalEdges.emplace_back(std::pair<uint32_t, uint32_t>{i, mAdjacency.at(i).at(j)});
//            }
//        }
//        return bidirectionalEdges;
//    }

//    std::vector<uint32_t> DFS(uint32_t startVertexIdx)
//    {
//        std::vector<uint32_t> dfs{};
//        std::vector<bool> visited{};
//        visited.resize(mAdjacency.size());
//        recursiveDFS(startVertexIdx, dfs, visited);
//        return dfs;
//    }

//    void recursiveDFS(uint32_t idx, std::vector<uint32_t>& dfs, std::vector<bool>& visited)
//    {
//        if(visited.at(idx))
//            return;

//        visited.at(idx) = true;
//        dfs.emplace_back(idx); // "process"
//        auto vertices = mAdjacency.at(idx);
//        for(uint32_t j = 0; j < vertices.size(); ++j)
//        {
//            if(!visited.at(vertices.at(j)))
//                recursiveDFS(vertices.at(j), dfs, visited);
//        }
//    }

//    std::stack<uint32_t> topologicalSort()
//    {
//        std::stack<uint32_t> sorted{};
//        std::vector<bool> visited{};
//        visited.resize(mAdjacency.size());

//        for(uint32_t i = 0; i < mAdjacency.size(); ++i)
//        {
//            if(visited.at(i) == false)
//                topologicalSortRecursive(i, sorted, visited);
//        }
//        return sorted;
//    }

//    void topologicalSortRecursive(uint32_t idx, std::stack<uint32_t>& sorted, std::vector<bool>& visited)
//    {
//        visited.at(idx) = true;

//        for(auto& el : mAdjacency.at(idx))
//        {
//            if(visited.at(el) == false)
//                topologicalSortRecursive(el, sorted, visited);
//        }

//        sorted.push(idx);
//    }

//    void show()
//    {
//        for(uint32_t i = 0; i < mAdjacency.size(); ++i)
//        {
//            std::cout << i << ": ";
//            for(uint32_t j = 0; j < mAdjacency.at(i).size(); ++j)
//            {
//                std::cout << mAdjacency.at(i).at(j) << " ";
//            }
//            std::cout << std::endl;
//        }
//    }

//private:
//    std::vector<std::vector<uint32_t>> mAdjacency;
//};

//namespace detail {
//    template <typename First, typename Second>
//    void printElement(const std::pair<First, Second>& pr)
//    {
//        std::cout << pr.first << " " << pr.second << " ";
//    }

//    template <typename Type>
//    void printElement(const Type& element)
//    {
//        std::cout << element << " ";
//    }
//} // namespace detail

//template<typename T>
//void displayContainer(const T& container)
//{
//    for(const auto& el : container)
//        detail::printElement(el);
//    std::cout << std::endl;
//}

#include <deque>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    AdjacencyList adjacencyList{5};
//    adjacencyList.addEdge(0, 7);
//    adjacencyList.addEdge(8, 10);
//    adjacencyList.addEdge(3, 6);
//    adjacencyList.addEdge(4, 5);
//    adjacencyList.addEdge(2, 6);
//    adjacencyList.addEdge(6, 8);
//    adjacencyList.addEdge(5, 9);
//    adjacencyList.addEdge(8, 9);
//    adjacencyList.addEdge(9, 11);
//    adjacencyList.addEdge(7, 8);
//    adjacencyList.addEdge(1, 7);
    adjacencyList.addEdge(0, 2);
    adjacencyList.addEdge(1, 3);
    adjacencyList.addEdge(2, 3);
    adjacencyList.addEdge(3, 2);
    adjacencyList.addEdge(2, 4);

    adjacencyList.show();

    std::cout << "---------------------- Topological sort ---------------------" << std::endl;
    auto sort = adjacencyList.topologicalSort();

    while (sort.empty() == false)
    {
        std::cout << sort.top() << " ";
        sort.pop();
    }

    return a.exec();
}
