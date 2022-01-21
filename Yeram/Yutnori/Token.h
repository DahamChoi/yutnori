#pragma once
#include "Map.h"

struct Token {
	char shape; //�� ���
	bool active;
	bool exit;
	int localOffset;//���� ���� �ɶ� ����ó��
	Space* currentSpace;
	Space* startSpace;
	int setLocalOffset(int index)
	{
		switch (index)
		{
		case 0:
			return 0;
		case 1:
			return 1;
		case 2:
			return (WIDTH + 1);
		case 3:
			return (WIDTH + 1) + 1;
		}
	}

public:
	Token(char shape, Map* map) :localOffset(0), shape(shape), active(false), exit(false)
	{
		startSpace = map->linker->getHead();
		currentSpace = startSpace;
		localOffset = setLocalOffset(shape - 'A');
	}

	void moveNext()//�������� �̵�.
	{
		if (active && currentSpace == startSpace) exit = true;
		if (!active) active = true;
		currentSpace = currentSpace->link;
	}

	const bool isActive() { return active; }
	const bool isExit() { return exit; }
	const char getShape() const { return shape; }
	const int getOffset() const {
		if (0 <= currentSpace->getOffset() && currentSpace->getOffset() <= WIDTH - 2 && 'B' < shape)return currentSpace->getOffset() + localOffset + 1;
		return currentSpace->getOffset() + localOffset;
	}
};