#pragma once

#include <iostream>
#include <vector>
#include <string>

#include "Node.h"


class Map
{
public:
	void ClearBuffer();
	void AddUnitBuffer(const std::vector<NodePtr>& vecNode);
	inline void AddNodeBuffer(const std::vector<NodePtr>& vecNode, int number, int x, int y);

public:
	void Draw();

private:
	std::vector<std::string> _Buffer;

};

