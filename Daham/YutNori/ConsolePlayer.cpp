#include "ConsolePlayer.h"

#include <algorithm>
#include <string>
#include <iostream>

Task::GameInputValue ConsolePlayer::Input()
{
    char type;             std::cin >> type;
    std::string strForce;  std::cin >> strForce;

    int force = std::count(strForce.begin(), strForce.end(), 'F');
    force = force == 0 ? 5 : force;

    return { type, force };
}
