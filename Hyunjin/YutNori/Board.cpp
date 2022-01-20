#include "Board.h"

#include <algorithm>

void Board::Init()
{
	vecNode.reserve(31);
	for (int idx = 0; idx < 31; idx++)
	{
		vecNode.push_back(std::make_shared<node>());
	}

	for (int idx = 0; idx < 4; idx++)
	{
		choices['a' + idx] = 0;
		choices['A' + idx] = 0;
	}

}

void Board::Task(const Player::GameInputValue & gameInputValue)
{
	static std::set<char> finished;

	const auto type = gameInputValue.type;
	const auto force = gameInputValue.force;

	int weight{}, nextPlace, team;

	if (finished.count(type) == 1) return;

	if (choices[type] == 5 || choices[type] == 10) weight = 15;

	nextPlace = choices[type] + force + weight;

	if (nextPlace == 23) nextPlace += 5;
	else if ((20 < choices[type] && choices[type] <= 25 && nextPlace > 25) || nextPlace == 31)
		nextPlace -= 11;

	if ((nextPlace > 20 && choices[type] + weight <= 20 && choices[type] > 15) || nextPlace > 31)
	{
		for (auto chessman : vecNode[choices[type]]->_Unit) finished.insert(chessman);

		vecNode[choices[type]]->_Unit.clear();
		return;
	}

	if ('A' <= type && type <= 'D') team = 0;
	else team = 1;

	auto pEnemyUnit = std::find_if(vecNode[nextPlace]->_Unit.begin(), vecNode[nextPlace]->_Unit.end(),
		[type, team](const char& _Unit)
		{
			if ((team == 0 && 'a' <= _Unit && _Unit <= 'd') ||
				(team == 1 && 'A' <= _Unit && _Unit <= 'D')) 
				return true;

			return false;
		});

	if (pEnemyUnit != vecNode[nextPlace]->_Unit.end())
	{
		for (auto chessman : vecNode[nextPlace]->_Unit) choices[chessman] = 0;

		vecNode[nextPlace]->_Unit.clear();
	}

	for (auto chessman : vecNode[choices[type]]->_Unit) vecNode[nextPlace]->_Unit.insert(chessman);

	vecNode[nextPlace]->_Unit.insert(type);
	vecNode[choices[type]]->_Unit.clear();

	for (auto chessman : vecNode[nextPlace]->_Unit) choices[chessman] = nextPlace;

}