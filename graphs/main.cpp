#include <QCoreApplication>

#include "adjacencylist.h"
#include "box.h"
#include "orgate.h"
#include "switch.h"
#include "andgate.h"
#include "notgate.h"

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

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    std::shared_ptr<Switch> switch1 = std::make_shared<Switch>();
    std::shared_ptr<Switch> switch2 = std::make_shared<Switch>();
    std::shared_ptr<Switch> switch3 = std::make_shared<Switch>();
    std::shared_ptr<Switch> switch4 = std::make_shared<Switch>();
    std::shared_ptr<OrGate> or1 = std::make_shared<OrGate>(2);
    std::shared_ptr<OrGate> or2 = std::make_shared<OrGate>(2);
    std::shared_ptr<AndGate> and1 = std::make_shared<AndGate>(2);
    std::shared_ptr<NotGate> not1 = std::make_shared<NotGate>();
    Box circuit{0, 0};
    circuit.addElement(switch1); // 0
    circuit.addElement(switch2); // 1
    circuit.addElement(switch3); // 2
    circuit.addElement(switch4); // 3
    circuit.addElement(or1); // 4
    circuit.addElement(or2); // 5
    circuit.addElement(and1); // 6
    circuit.addElement(not1); // 7

    //switch1->toggleOutput();
    //switch2->toggleOutput();
    //switch3->toggleOutput();
    //switch4->toggleOutput();

    circuit.createConnectionBetweenElements(switch1->getIdx(), or1->getIdx(), 0, 0);
    circuit.createConnectionBetweenElements(switch2->getIdx(), or1->getIdx(), 1, 0);

    circuit.createConnectionBetweenElements(switch3->getIdx(), or2->getIdx(), 0, 0);
    circuit.createConnectionBetweenElements(switch4->getIdx(), or2->getIdx(), 1, 0);

    circuit.createConnectionBetweenElements(or1->getIdx(), and1->getIdx(), 0, 0);
    circuit.createConnectionBetweenElements(or2->getIdx(), and1->getIdx(), 1, 0);

    circuit.createConnectionBetweenElements(and1->getIdx(), not1->getIdx(), 0, 0);

    circuit.process();

    std::cout << "Output: " << not1->getOutput(0)->getVal() << std::endl;

    return a.exec();
}
