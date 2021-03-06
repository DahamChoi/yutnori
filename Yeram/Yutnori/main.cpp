#include <iostream>
#include <vector>
using namespace std;

#define WIDTH 32
#define HEIGHT 32
#define SIZE 33*32

//part of Map -> map의 구성요소이다.
typedef struct Space
{
	bool isEdge;//모서리인지 아닌지.
	int offset;//map상에서의 offset(position)
	//vector<Space*> link; //다음 Space 가르키는 주소<
	Space* link; //다음 Space 가르키는 주소

	void createSpace(Space* head, Space* prevNode, int offset, char* map,bool isEdge = false)
	{
		//headnode,prevnode NULL 체크
		if (head == NULL || prevNode == NULL) exit(1);

		this->isEdge = isEdge; 
		this->offset = offset;

		prevNode->link = this;
		link = head;//원형리스트

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

				//대각선
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
	void linkSpace(Space* head, Space* startNode) {
		Space* temp = startNode; //임시 pointer

		for (int i = (WIDTH + 1) * (HEIGHT - 1) - 2 - (WIDTH + 1) * 6; WIDTH < i; i -= (WIDTH + 1) * 6)
		{
			Space* node = new Space;
			node->createSpace(head, temp, i, map);
			temp = node;
		}
	}
public:
	Map():map(new char[SIZE + 1]),head(new Space)
	{
		memset(map, ' ', SIZE);
		map[SIZE] = '\0';
		drawLine();
	}

	//함수 내부에서 space들을 link 시킨다.
	void createMap()
	{
		head->createSpace(head, head, (WIDTH + 1) * (HEIGHT - 1) - 2, map);

		linkSpace(head, head);

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

	//얘는 말 구조체가 수행해야 할 함수 인 것 같다.
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
	
	printf("4이하의 숫자 입력\n");
	scanf("%d", &count);
	map.moveNext(count);

	printf("%s", map.getMap());

	
}