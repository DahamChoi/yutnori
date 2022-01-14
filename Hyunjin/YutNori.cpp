#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>

#define MAXSIZE 32

using namespace std;

void initBoard(vector<string>& board)
{
	for (int i = 0; i < MAXSIZE; i++)
	{
		if (i == 0 || i == MAXSIZE - 1) board[i] = "--------------------------------";
		else board[i] = "|                              |";

		board[i][i] = '\\';
		board[i][MAXSIZE - i - 1] = '/';
	}
}

bool isEnemy(const set<char>& block, const int type)
{
	if (block.empty()) return false;

	if (type == 0)
		for (auto choice : block)
			if ('A' <= choice && choice <= 'D') return false;

	if (type == 1)
		for (auto choice : block)
			if ('a' <= choice && choice <= 'd') return false;

	return true;
}

void updateBlock(vector<set<char>>& blocks, map<char, int>& choices)
{
	static set<char> finished;
	char choice;
	string info;
	int move = 0, nextPlace, choiceType, weight = 0;

	cin >> choice;
	cin >> info;

	if (finished.count(choice) == 1) return;

	for (int i = 0; i < info.size(); i++)
		if (info[i] == 'F') move++;

	if (move == 0) move = 5;

	if (choices[choice] == 5 || choices[choice] == 10) weight = 15;

	nextPlace = choices[choice] + move + weight;

	if (nextPlace == 23) nextPlace += 5;
	else if ((20 < choices[choice] && choices[choice] <= 25 && nextPlace > 25) || nextPlace == 31)
		nextPlace -= 11;

	if ((nextPlace > 20 && choices[choice] + weight <= 20 && choices[choice] > 15) || nextPlace > 31)
	{
		for (auto chessman : blocks[choices[choice]]) finished.insert(chessman);

		blocks[choices[choice]].clear();
		return;
	}


	if ('A' <= choice && choice <= 'D') choiceType = 0;
	else choiceType = 1;

	if (isEnemy(blocks[nextPlace], choiceType))
	{
		for (auto chessman : blocks[nextPlace]) choices[chessman] = 0;

		blocks[nextPlace].clear();
	}

	for(auto chessman : blocks[choices[choice]]) blocks[nextPlace].insert(chessman);

	blocks[nextPlace].insert(choice);
	blocks[choices[choice]].clear();

	for (auto chessman : blocks[nextPlace]) choices[chessman] = nextPlace;

}

void drawChessman(vector<string>& board, const vector<set<char>>& blocks, int number, int x, int y)
{
	for (int i = 0; i < 4; i++)
		if (blocks[number].count('a' + i) == 1) board[x + i / 2][y + i % 2] = 'a' + i;
		else if (blocks[number].count('A' + i) == 1) board[x + i / 2][y + i % 2] = 'A' + i;
		else board[x + i / 2][y + i % 2] = '.';

}

void drawBoard(vector<string>& board, const vector<set<char>>& blocks)
{
	for (int i = 1; i <= 5; i++) drawChessman(board, blocks, i, 6 * (5 - i), 6 * 5);
	for (int i = 6; i <= 10; i++) drawChessman(board, blocks, i, 0, 6 * (5 - (i - 5)));
	for (int i = 11; i <= 15; i++) drawChessman(board, blocks, i, 6 * (i - 10), 0);
	for (int i = 16; i <= 20; i++) drawChessman(board, blocks, i, 6 * 5, 6 * (i - 15));
	for (int i = 21; i <= 25; i++) drawChessman(board, blocks, i, 5 * (i - 20), 5 * (6 - (i - 20)));
	for (int i = 26; i <= 30; i++) drawChessman(board, blocks, i, 5 * (i - 25), 5 * (i - 25));

}

void printBoard(const vector<string>& board)
{
	for (auto line : board)	cout << line << endl;
}

int main()
{
	vector<string> board(MAXSIZE);
	vector<set<char>> blocks(31);
	map<char, int> choices;
	int input;

	initBoard(board);

	for (int i = 0; i < 4; i++)
	{
		choices['a' + i] = 0;
		choices['A' + i] = 0;
	}

	cin >> input;
	for (int i = 0; i < input; i++) updateBlock(blocks, choices);

	drawBoard(board, blocks);
	printBoard(board);

	return 0;
}