#include "Map.h"

void Map::ClearBuffer()
{
	if (_Buffer.empty())
	{
		_Buffer.reserve(MAXSIZE);
		for (int idx = 0; idx < MAXSIZE; idx++) _Buffer.push_back("");
	}

	for (int i = 0; i < MAXSIZE; i++)
	{
		if (i == 0 || i == MAXSIZE - 1) _Buffer[i] = "--------------------------------";
		else _Buffer[i] = "|                              |";

		_Buffer[i][i] = '\\';
		_Buffer[i][MAXSIZE - i - 1] = '/';
	}
}

inline void Map::AddNodeBuffer(const std::vector<NodePtr>& vecNode, int number, int x, int y)
{
	for (int i = 0; i < 4; i++)
		if (vecNode[number]->_Unit.count('a' + i) == 1) _Buffer[x + i / 2][y + i % 2] = 'a' + i;
		else if (vecNode[number]->_Unit.count('A' + i) == 1) _Buffer[x + i / 2][y + i % 2] = 'A' + i;
		else _Buffer[x + i / 2][y + i % 2] = '.';

}

void Map::AddUnitBuffer(const std::vector<NodePtr>& vecNode)
{
		for (int i = 1; i <= 5; i++) AddNodeBuffer(vecNode, i, 6 * (5 - i), 6 * 5);
		for (int i = 6; i <= 10; i++) AddNodeBuffer(vecNode, i, 0, 6 * (5 - (i - 5)));
		for (int i = 11; i <= 15; i++) AddNodeBuffer(vecNode, i, 6 * (i - 10), 0);
		for (int i = 16; i <= 20; i++) AddNodeBuffer(vecNode, i, 6 * 5, 6 * (i - 15));
		for (int i = 21; i <= 25; i++) AddNodeBuffer(vecNode, i, 5 * (i - 20), 5 * (6 - (i - 20)));
		for (int i = 26; i <= 30; i++) AddNodeBuffer(vecNode, i, 5 * (i - 25), 5 * (i - 25));
}

void Map::Draw()
{
	for (auto line : _Buffer)	std::cout << line << std::endl;
}
