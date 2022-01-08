#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>
#include <algorithm>
#include <memory>

enum class E_NEXT_NODE_TYPE
{
     FORKED_ROAD,
     NORMAL_ROAD,
};

struct node
{
    unsigned int _Unit{ };
    std::unordered_map<E_NEXT_NODE_TYPE, std::shared_ptr<node>> _NextNodeMap{ };
}; using NodePtr = std::shared_ptr<node>;

std::vector<NodePtr> vecNode;

void MoveNode(const NodePtr& pNode, const unsigned int eraseBit, const unsigned int orBit)
{
    if (nullptr == pNode)
        return;

    pNode->_Unit = (pNode->_Unit & eraseBit) | orBit;
}

void Task(char type, int force)
{
    char bitSequence = type >= 'A' && type <= 'Z' ? type - 'A' + 4 : type - 'a';

    auto pUnitNode = std::find_if(vecNode.begin(), vecNode.end(),
        [bitSequence](const NodePtr& pNode)
        {
            return (pNode->_Unit & (1 << bitSequence));
        });

    pUnitNode = pUnitNode == vecNode.end() ? vecNode.begin() : pUnitNode;

    auto pNextUnitNode = *pUnitNode;
    int forceCounter = force;
    while (pNextUnitNode != nullptr && forceCounter > 0)
    {
        pNextUnitNode = 
            forceCounter-- == force && pNextUnitNode->_NextNodeMap.find(E_NEXT_NODE_TYPE::FORKED_ROAD) != pNextUnitNode->_NextNodeMap.end() ? 
            pNextUnitNode->_NextNodeMap[E_NEXT_NODE_TYPE::FORKED_ROAD] : pNextUnitNode->_NextNodeMap[E_NEXT_NODE_TYPE::NORMAL_ROAD];
    }

    const auto eraseBit = bitSequence >= 4 ? 0b11110000 : 0b00001111;
    const auto orBit = (*pUnitNode)->_Unit | (1 << bitSequence);
    MoveNode(pNextUnitNode, eraseBit, orBit);
    MoveNode(pNextUnitNode == vecNode[25] ? vecNode[30] : pNextUnitNode == vecNode[30] ? vecNode[25] : nullptr, eraseBit, orBit);

    (*pUnitNode)->_Unit = 0;
}

void Draw()
{
    std::vector<std::string> origin = 
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

    static std::map<int, std::pair<int, int>> indexToPositionMap =
    {
        { 1,  {31,25} }, { 2,  {31,19} }, { 3,  {31,13} }, { 4,  {31,7}  }, { 5,  {31,1}  },
        { 6,  {25,1}  }, { 7,  {19,1}  }, { 8,  {13,1}  }, { 9,  {7,1}   }, { 10, {1,1}   },
        { 11, {1,7}   }, { 12, {1,13}  }, { 13, {1,19}  }, { 14, {1,25}  }, { 15, {1,31}  },
        { 16, {7,31}  }, { 17, {13,31} }, { 18, {19,31} }, { 19, {25,31} }, { 20, {31,31} },
        { 21, {6,6}   }, { 22, {26,6}  }, { 23, {11,11} }, { 24, {21,11} }, { 25, {16,16} },
        { 26, {11,21} }, { 27, {21,21} }, { 28, {6,26}  }, { 29, {26,26} },
    };

    for (int idx = 1; idx < 30; idx++)
    {
        const auto& pNode = vecNode[idx];
        auto position = indexToPositionMap[idx];
        position.first -= 1;    position.second -= 1;

        origin[position.second][position.first]         = (pNode->_Unit & (1 << 0) ? 'a' : pNode->_Unit & (1 << 4) ? 'A' : '.');
        origin[position.second][position.first + 1]     = (pNode->_Unit & (1 << 1) ? 'b' : pNode->_Unit & (1 << 5) ? 'B' : '.');
        origin[position.second + 1][position.first]     = (pNode->_Unit & (1 << 2) ? 'c' : pNode->_Unit & (1 << 6) ? 'C' : '.');
        origin[position.second + 1][position.first + 1] = (pNode->_Unit & (1 << 3) ? 'd' : pNode->_Unit & (1 << 7) ? 'D' : '.');
    }

    for (const auto& line : origin)
    {
        std::cout << line << '\n';
    }
}

int main()
{
    vecNode.reserve(31);
    for (int idx = 0; idx < 31; idx++)
    {
        vecNode.push_back(std::make_shared<node>());
    }

    for (int idx = 0; idx < 20; idx++)
    {
        vecNode[idx]->_NextNodeMap[E_NEXT_NODE_TYPE::NORMAL_ROAD] = vecNode[idx + 1];
    }

    vecNode[5]->_NextNodeMap[E_NEXT_NODE_TYPE::FORKED_ROAD]  = vecNode[22];
    vecNode[10]->_NextNodeMap[E_NEXT_NODE_TYPE::FORKED_ROAD] = vecNode[21];
    vecNode[21]->_NextNodeMap[E_NEXT_NODE_TYPE::NORMAL_ROAD] = vecNode[23];
    vecNode[23]->_NextNodeMap[E_NEXT_NODE_TYPE::NORMAL_ROAD] = vecNode[30];
    vecNode[22]->_NextNodeMap[E_NEXT_NODE_TYPE::NORMAL_ROAD] = vecNode[24];
    vecNode[24]->_NextNodeMap[E_NEXT_NODE_TYPE::NORMAL_ROAD] = vecNode[25];
    vecNode[25]->_NextNodeMap[E_NEXT_NODE_TYPE::FORKED_ROAD] = vecNode[27];
    vecNode[25]->_NextNodeMap[E_NEXT_NODE_TYPE::NORMAL_ROAD] = vecNode[26];
    vecNode[26]->_NextNodeMap[E_NEXT_NODE_TYPE::NORMAL_ROAD] = vecNode[28];
    vecNode[28]->_NextNodeMap[E_NEXT_NODE_TYPE::NORMAL_ROAD] = vecNode[15];
    vecNode[27]->_NextNodeMap[E_NEXT_NODE_TYPE::NORMAL_ROAD] = vecNode[29];
    vecNode[29]->_NextNodeMap[E_NEXT_NODE_TYPE::NORMAL_ROAD] = vecNode[20];
    vecNode[30]->_NextNodeMap[E_NEXT_NODE_TYPE::NORMAL_ROAD] = vecNode[27];

    int N;  std::cin >> N;
    for (int idx = 0; idx < N; idx++)
    {
        char type;             std::cin >> type;
        std::string strForce;  std::cin >> strForce;

        int force = std::count(strForce.begin(), strForce.end(), 'F');
        force = force == 0 ? 5 : force;

        Task(type, force);
    }

    Draw();

    return 0;
}