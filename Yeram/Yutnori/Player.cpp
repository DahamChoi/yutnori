#include "Player.h"

void Player::moveToken(string turn)
{
	int index = turn.front() - tokens.front().getShape();//token�� �̸�
	int step = 0;
	for (auto data : turn)//B,F ���� Ȯ��
	{
		if (data == 'F') step++;
	}

	if (step == 0) step = 5;
	while (step != 0)
	{
		tokens[index].moveNext();
		step--;
	}
}
