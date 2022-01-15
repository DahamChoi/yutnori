#pragma once

#include <memory>
#include <unordered_map>

enum class E_NEXT_NODE_TYPE
{
    FORKED_ROAD,
    NORMAL_ROAD,
};

struct node
{
    unsigned int _Idx{ };
    unsigned int _Unit{ };
    std::unordered_map<E_NEXT_NODE_TYPE, std::shared_ptr<node>> _NextNodeMap{ };
}; using NodePtr = std::shared_ptr<node>;
