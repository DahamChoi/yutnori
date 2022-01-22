#pragma once

#include "IBoard.h"

class IPlayer
{
public:
	virtual Task::GameInputValue Input() = 0;
};