#include "Board.h"

#include "ConsoleNode.h"

#include <memory>
#include <cassert>

Board::Board()
{
    vecNode.reserve(31);
    for (int idx = 0; idx < 31; idx++)
    {
        vecNode.push_back(MakeNodePtr());
    }

    for (int idx = 0; idx < 20; idx++)
    {
        vecNode[idx]->_NextNodeMap[E_NEXT_NODE_TYPE::NORMAL_ROAD] = vecNode[idx + 1];
    }

    vecNode[5]->_NextNodeMap[E_NEXT_NODE_TYPE::FORKED_ROAD] = vecNode[22];
    vecNode[10]->_NextNodeMap[E_NEXT_NODE_TYPE::FORKED_ROAD] = vecNode[21];
    vecNode[21]->_NextNodeMap[E_NEXT_NODE_TYPE::NORMAL_ROAD] = vecNode[23];
    vecNode[23]->_NextNodeMap[E_NEXT_NODE_TYPE::NORMAL_ROAD] = vecNode[30];
    vecNode[22]->_NextNodeMap[E_NEXT_NODE_TYPE::NORMAL_ROAD] = vecNode[24];
    vecNode[24]->_NextNodeMap[E_NEXT_NODE_TYPE::NORMAL_ROAD] = vecNode[25];
    vecNode[25]->_NextNodeMap[E_NEXT_NODE_TYPE::FORKED_ROAD] = vecNode[27];
    vecNode[25]->_NextNodeMap[E_NEXT_NODE_TYPE::NORMAL_ROAD] = vecNode[26];
    vecNode[26]->_NextNodeMap[E_NEXT_NODE_TYPE::NORMAL_ROAD] = vecNode[28];
    vecNode[28]->_NextNodeMap[E_NEXT_NODE_TYPE::NORMAL_ROAD] = vecNode[15];
    vecNode[27]->_NextNodeMap[E_NEXT_NODE_TYPE::NORMAL_ROAD] = vecNode[29];
    vecNode[29]->_NextNodeMap[E_NEXT_NODE_TYPE::NORMAL_ROAD] = vecNode[20];
    vecNode[30]->_NextNodeMap[E_NEXT_NODE_TYPE::NORMAL_ROAD] = vecNode[27];
}

void Board::Task(const Task::GameInputValue& gameInputValue)
{
    const auto type = gameInputValue.type;
    const auto force = gameInputValue.force;

    char bitSequence = type >= 'A' && type <= 'Z' ? type - 'A' + 4 : type - 'a';

    auto pUnitNode = std::find_if(vecNode.begin(), vecNode.end(),
        [bitSequence](const NodePtr& pNode)
        {
            return (pNode->_Unit & (1 << bitSequence));
        });

    pUnitNode = pUnitNode == vecNode.end() ? vecNode.begin() : pUnitNode;

    auto pNextUnitNode = *pUnitNode;
    int forceCounter = force;
    while (pNextUnitNode != nullptr && forceCounter > 0)
    {
        pNextUnitNode =
            forceCounter-- == force && pNextUnitNode->_NextNodeMap.find(E_NEXT_NODE_TYPE::FORKED_ROAD) != pNextUnitNode->_NextNodeMap.end() ?
            pNextUnitNode->_NextNodeMap[E_NEXT_NODE_TYPE::FORKED_ROAD] : pNextUnitNode->_NextNodeMap[E_NEXT_NODE_TYPE::NORMAL_ROAD];
    }

    const auto eraseBit = bitSequence >= 4 ? 0b11110000 : 0b00001111;
    const auto orBit = (*pUnitNode)->_Unit | (1 << bitSequence);
    MoveNode(pNextUnitNode, eraseBit, orBit);
    MoveNode(pNextUnitNode == vecNode[25] ? vecNode[30] : pNextUnitNode == vecNode[30] ? vecNode[25] : nullptr, eraseBit, orBit);

    (*pUnitNode)->_Unit = 0;
}

void Board::MoveNode(const NodePtr& pNode, const unsigned int eraseBit, const unsigned int orBit)
{
    if (nullptr == pNode)
        return;

    pNode->_Unit = (pNode->_Unit & eraseBit) | orBit;
}

NodePtr ConsoleBoard::MakeNodePtr()
{
    auto ret = std::make_shared<ConsoleNode>();
    return ret;
}

void ConsoleBoard::DrawBoardUnit(IGraphics* pGraphics)
{
    for (int idx = 1; idx < 30; idx++)
    {
        auto pNode = std::dynamic_pointer_cast<ConsoleNode>(vecNode[idx]);
        if (nullptr != pNode)
        {
            pNode->DrawGraphicsObject(pGraphics);
        }
    }
}
