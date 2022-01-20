#pragma once

#include <set>

#define MAXSIZE 32

struct node
{
	std::set<char> _Unit{};
}; using NodePtr = std::shared_ptr<node>;
