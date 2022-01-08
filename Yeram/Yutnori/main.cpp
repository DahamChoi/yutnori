#include <iostream>
#include <vector>
using namespace std;

#define WIDTH 32
#define HEIGHT 32
#define SIZE 33*32

enum class Direction {
	UP,
	DOWN,
	RIGHT,
	LEFT
};

//part of Map -> map�� ��������̴�.
typedef struct Space
{
	bool isEdge;//�𼭸����� �ƴ���.
	int offset;//map�󿡼��� offset(position)
	//vector<Space*> link; //���� Space ����Ű�� �ּ�<
	Space* link; //���� Space ����Ű�� �ּ�

	void createSpace(Space* head, Space* prevNode, int offset, char* map,bool isEdge = false)
	{
		//headnode,prevnode NULL üũ
		if (head == NULL || prevNode == NULL) exit(1);

		this->isEdge = isEdge; 
		this->offset = offset;

		prevNode->link = this;
		link = head;//��������Ʈ

		drawSpace(offset, map);
	}

	void drawSpace(int offset, char* map) //offset = array index
	{
		int secondline = WIDTH + 1;
		if(0<= offset && offset<=WIDTH) secondline = WIDTH + 2;
		map[offset] = '.';
		map[offset+1] = '.';
		map[offset+ secondline] = '.';
		map[offset + secondline + 1] = '.';
	}

	void movePiece(char* map)
	{
		map[offset] = 'C';
	}
}Space;


typedef struct Map
{
private:
	char* map;
	Space* head;

	int nextOffset(Direction dir) {
		switch (dir)
		{
		case Direction::UP:
			return -(WIDTH + 1) * 6;
		case Direction::DOWN:
			return (WIDTH + 1) * 6;
		case Direction::RIGHT:
			return 6;
		case Direction::LEFT:
			return -6;
		default:
			break;
		}
	}

	//draw line of map
	void drawLine()
	{
		//DrawLine
		int diagcount = 0;//diagonal count
		for (int i = 0; i < SIZE; i++)
		{
			if ((0 <= i && i < WIDTH) || ((WIDTH + 1) * (HEIGHT - 1) - 1 <= i && i < SIZE)) map[i] = '-';
			if (WIDTH < i && i % (WIDTH + 1) == 0)
			{
				if (i != WIDTH + 1) map[i - 1] = '|';
				map[i] = '\n';
				map[i + 1] = '|';

				//�밢��
				if (diagcount != HEIGHT)
				{
					diagcount++;
					map[(i + 1) + diagcount] = '\\';
					map[(i + WIDTH) - diagcount] = '/';
				}
			}
		}	
	}

	//linking Space node
	Space* linkSpace(Space* head, Space* startNode, int endOffset, Direction dir) {
		Space* temp = startNode; //�ӽ� pointer

		//(WIDTH + 1) * (HEIGHT - 1) - 2 - (WIDTH + 1) * 6

#if bug //�Ʒ���for���� while������ �ٲٰ� ������, ������ �и� ���� �� ������ �۵��� �� �ȵȴ�..����//
		int offset = startNode->offset + nextOffset(dir);
  
		while (true) {
			
			Space* node = new Space;
			node->createSpace(head, temp, offset, map);
			temp = node;

			offset += nextOffset(dir);

			if (endOffset <= offset) break;
		}
#endif
		for (int i = startNode->offset + nextOffset(dir); endOffset <= i; i += nextOffset(dir))
		{
			Space* node = new Space;
			node->createSpace(head, temp, i, map);
			temp = node;
		}

		return temp; //return lastNode
	}
public:
	Map():map(new char[SIZE + 1]),head(new Space)
	{
		memset(map, ' ', SIZE);
		map[SIZE] = '\0';
		drawLine();
	}

	//�Լ� ���ο��� space���� link ��Ų��.
	void createMap()
	{
		head->createSpace(head, head, (WIDTH + 1) * (HEIGHT - 1) - 2, map);

		Space* lastSpace = linkSpace(head, head, WIDTH,Direction::UP);
		
		Space* Edge = new Space;
		Edge->createSpace(head, lastSpace, lastSpace->offset + nextOffset(Direction::UP) - 1, map);
		lastSpace = linkSpace(head, Edge, 1, Direction::LEFT);

#if debug
		for (int i = 6; i < WIDTH - 6; i += 6)
		{
			//up
			Space* node = new Space;
			node->createSpace(head, temp, i, map);

			//down
			node = new Space;
			node->createSpace(head, temp, i + (WIDTH + 1) * (HEIGHT - 2) + 1, map);

			//left
			node = new Space;
			node->createSpace(head, temp, (WIDTH + 1) * i + 1, map);

			//right
			node = new Space;
			node->createSpace(head, temp, (WIDTH + 1) * (i + 1) - 2, map);
		}
#endif	
		return;
	}

	char* getMap() { return map; }

	//��� �� ����ü�� �����ؾ� �� �Լ� �� �� ����.
	void moveNext(int count)
	{
		Space* tmp=head;
		while (1)
		{
			printf("OFSSET: %d\n", tmp->offset);
			if (count == 0)
			{
				tmp->movePiece(map);
				break;
			}
			
			tmp = tmp->link;		
			count--;
		}

		
	}
};



int main()
{
	int count;
	Map map = Map();
	map.createMap();
	
	printf("9������ ���� �Է�\n");
	scanf("%d", &count);
	map.moveNext(count);

	printf("%s", map.getMap());

	
}