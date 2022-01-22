#pragma once

#include "IPlayer.h"

class ConsolePlayer : public IPlayer
{
public:
    virtual Task::GameInputValue Input() override;
};

