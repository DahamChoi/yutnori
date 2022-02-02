#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <cstring>
using namespace std;

class Space
{
public:
	Space* link;
	pair<int, int> pos;

	Space(Space* head, Space* prevNode, pair<int, int> pos)
	{
		this->pos = pos;
		link = head;//��������Ʈ
	}
};

class Token
{
private:
	Space* head;
public:
	bool isActive;
	char shape;
	Space* space;
	Token(char shape, Space* head) :shape(shape), space(head), head(head), isActive(true) {}
	void moveNext()
	{
		space = space->link;
		if (space == head)isActive = false;
	}

	pair<int, int> getPos()
	{
		if (shape == 'A')
			return space->pos;
		else if (shape == 'B')
			return make_pair(space->pos.first + 1, space->pos.second);
		else if (shape == 'C')
			return make_pair(space->pos.first, space->pos.second + 1);
		else if (shape == 'D')
			return make_pair(space->pos.first + 1, space->pos.second + 1);
	}

	pair<int, int> getSpacePos()
	{
		return space->pos;
	}

	void setAvtive() {
		isActive = true;
	}

};

void linkSpace(Space* head)
{
	Space* temp = head;//�ӽ� ������
	//(30,Y) ��
	for (int i = 24; 0 <= i; i-=6)
	{
		Space* node = new Space(head, temp,make_pair(30, i));
		temp->link = node;
		temp = node;
	}
	//(0,Y)
	for (int i = 24; 0 <= i; i -= 6)
	{
		Space* node = new Space(head, temp, make_pair(i, 0));
		temp->link = node;
		temp = node;
	}

	//(X,0)
	for (int i = 6; i<= 30; i += 6)
	{
		Space* node = new Space(head, temp, make_pair(0, i));
		temp->link = node;
		temp = node;
	}
	//(X,30)
	for (int i = 6; i <30; i += 6)
	{
		Space* node = new Space(head, temp, make_pair(i,30));
		temp->link = node;
		temp = node;
	}
	//(X != Y)
	//(X == Y)
}

void drawMap(Space* head, vector<Token*> player)
{	
	vector<string> map =
	{
		"..----..----..----..----..----..",
		"..    ..    ..    ..    ..    ..",
		"| \\                          / |",
		"|  \\                        /  |",
		"|   \\                      /   |",
		"|    ..                  ..    |",
		"..   ..                  ..   ..",
		"..     \\                /     ..",
		"|       \\              /       |",
		"|        \\            /        |",
		"|         ..        ..         |",
		"|         ..        ..         |",
		"..          \\      /          ..",
		"..           \\    /           ..",
		"|             \\  /             |",
		"|              ..              |",
		"|              ..              |",
		"|             /  \\             |",
		"..           /    \\           ..",
		"..          /      \\          ..",
		"|         ..        ..         |",
		"|         ..        ..         |",
		"|        /            \\        |",
		"|       /              \\       |",
		"..     /                \\     ..",
		"..   ..                  ..   ..",
		"|    ..                  ..    |",
		"|   /                      \\   |",
		"|  /                        \\  |",
		"| /                          \\ |",
		"..    ..    ..    ..    ..    ..",
		"..----..----..----..----..----.."
	};

	Space* linker = head; //for Read
	
	//setAvtive()
	for (auto token : player)
	{
		if (!token->isActive) continue;

		string tmp_string(1, token->shape);
		map[token->getPos().second].replace(token->getPos().first, 1, tmp_string);
	}
	

	//�ڿ� \n �߰��ϱ�.
	vector<string>::iterator itor = map.begin();

	for (; itor != map.end(); itor++)
	{
		if(itor == map.end()-1)itor->push_back('\0');
		else itor->push_back('\n');
		char* cmap = new char[34];
		strcpy(cmap, itor->c_str());
		printf("%s", cmap);//���
	}
}

class Player
{

public:
	Space* head;
	vector<Token*> tokens;
	Player():head(nullptr)
	{
		head = new Space(head, head, make_pair(30, 30));
		linkSpace(head);
	}

	void work(int step,string turn)
	{
		//������ �������� ���� ���� �� �̵� ��Ų��.
		if (tokens.empty())//���� �ϳ��� ������ �����Ѵ�.
		{
			tokens.push_back(new Token(turn.front(), head));
		}

		Token* target = tokens.front();
		for (auto token : tokens)
		{
			if (to_string(token->shape) != to_string(turn.front())) continue;
			target = token;
			break;
		}

		if (to_string(target->shape) != to_string(turn.front()))
		{
			target = new Token(turn.front(), head);
			tokens.push_back(target);
		}

		vector<Token*> group;
		for (auto member : tokens)
		{
			if (target->getSpacePos() == member->getSpacePos()) group.push_back(member);
		}


		while (step != 0)
		{
			for (auto member : group)
			{
				member->moveNext();
			}
			step--;
		}
	}
};
int main()
{
	Player* p1= new Player();
	int count;
	string turn;

	int step = 0;

	scanf("%d ", &count);

	while (count != 0)
	{
		getline(cin, turn);

		for (auto data : turn)//B,F ���� Ȯ��
		{
			if (data == 'F') step++;
		}

		if (step == 0) step = 5;

		p1->work(step, turn);

		count--;
	}

	drawMap(p1->head, p1->tokens);
	return 0;
}