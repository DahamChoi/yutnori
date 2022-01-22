#pragma once

#define WIDTH 32
#define HEIGHT 32
#define SIZE 33*32

struct Space
{
private:
	bool isEdge;//�𼭸����� �ƴ���.
	int offset;//map�󿡼��� offset(position)
	//vector<Space*> link; //���� Space ����Ű�� �ּ�<
public:
	Space* link; //���� Space ����Ű�� �ּ�

	Space(Space* head, Space* prevNode, int offset, bool isEdge = false)
	{
		//headnode,prevnode NULL üũ
		if (head == NULL || prevNode == NULL) exit(0);

		this->isEdge = isEdge;
		this->offset = offset;
		link = head;//��������Ʈ
	}

	const int getOffset() const { return offset; };
};


