#pragma once

#include <vector>

#include "Player.h"
#include "Node.h"

class Board
{
public:
    void Init();

public:
    void Task(const Player::GameInputValue& gameInputValue);

public:
    const NodePtr& GetNode(int idx);

private:
    void MoveNode(const NodePtr& pNode, const unsigned int eraseBit, const unsigned int orBit);

private:
    std::vector<NodePtr> vecNode;
};
