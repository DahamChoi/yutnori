#include <iostream>
#include <vector>

#define WIDTH 32
#define HEIGHT 32
#define SIZE 33*32
using namespace std;

typedef struct Space
{
	bool isEdge;//�𼭸����� �ƴ���.
	int offset;//map�󿡼��� offset(position)
	//vector<Space*> link; //���� Space ����Ű�� �ּ�<
	Space* link; //���� Space ����Ű�� �ּ�

	void createSpace(Space* head, Space* prevNode, int offset, char* map,bool isEdge = false)
	{
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
	char* map;
	Space* head;

	Map()
	{
		map = new char[SIZE + 1];
		head = new Space;
		
	}

	char* drawMap()
	{
		memset(map, ' ', SIZE);
		map[SIZE] = '\0';

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

		//DrawSpace
		head->createSpace(head, head, (WIDTH + 1) * (HEIGHT - 1) - 2, map);
		Space* temp = head; //�ӽ� pointer

		/*Space* node = new Space;
		node->createSpace(head, temp, (WIDTH + 1) * (HEIGHT - 1) - 2 - (WIDTH+1)*6, map);*/
		//up
		for (int i = (WIDTH + 1) * (HEIGHT - 1) - 2 - (WIDTH + 1) * 6; WIDTH < i; i -= (WIDTH + 1) * 6)
		{
			Space* node = new Space;
			node->createSpace(head, temp, i, map);
			temp = node;
		}

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
		return map;
	}

	void moveNext(int count)
	{
		Space* tmp=head;
		while (1)
		{
			printf("OFSSET: %d\n", tmp->offset);
			if (count == 1)
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
	map.drawMap();
	
	printf("4������ ���� �Է�\n");
	scanf("%d", &count);
	map.moveNext(count);

	printf("%s", map.map);

	
}