#pragma once

#include <vector>
#include <map>

#include "Player.h"
#include "Node.h"

class Board
{
public:
	void Init();

public:
	void Task(const Player::GameInputValue& gameInputValue);

public:
	const std::vector<NodePtr>& GetVecNode() { return vecNode; }
private:
	std::vector<NodePtr> vecNode;
	std::map<char, int> choices;

};

