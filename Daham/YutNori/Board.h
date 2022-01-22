#pragma once

#include "IBoard.h"
#include "IGraphics.h"

#include <vector>

#include "Node.h"

class Board : public ITask, public IBoard
{
public:
    virtual void Task(const Task::GameInputValue& gameInputValue) override;
    virtual void DrawBoardUnit(IGraphics* pGraphics) = 0;

public:
    Board();

public:
    virtual NodePtr MakeNodePtr() = 0;

private:
    void MoveNode(const NodePtr& pNode, const unsigned int eraseBit, const unsigned int orBit);

protected:
    std::vector<NodePtr> vecNode;
};

class ConsoleBoard : public Board
{
public:
    virtual NodePtr MakeNodePtr() override;

public:
    virtual void DrawBoardUnit(IGraphics* pGraphics) override;
};