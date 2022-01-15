#pragma once

#include <string>
#include <iostream>

class Player
{
public:
    struct GameInputValue
    {
        char type;
        int force;
    };

public:
    GameInputValue Input();
};

