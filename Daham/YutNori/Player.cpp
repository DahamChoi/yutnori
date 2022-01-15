#include "Player.h"

Player::GameInputValue Player::Input()
{
    char type;             std::cin >> type;
    std::string strForce;  std::cin >> strForce;

    int force = std::count(strForce.begin(), strForce.end(), 'F');
    force = force == 0 ? 5 : force;

    return { type, force };
}
