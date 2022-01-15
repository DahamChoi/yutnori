#pragma once

#include "Node.h"

class Map
{
public:
    void ClearBuffer();
    void AddUnitBuffer(const NodePtr& pNode);

public:
    void Draw();

private:
    std::vector<std::string> _Buffer;
};