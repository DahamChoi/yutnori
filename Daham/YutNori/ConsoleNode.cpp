#include "ConsoleNode.h"
#include "ConsoleGraphics.h"

#include <map>

void ConsoleNode::DrawGraphicsObject(IGraphics* pGraph)
{
    static std::map<int, std::pair<int, int>> indexToPositionMap =
    {
        { 1,  {31,25} }, { 2,  {31,19} }, { 3,  {31,13} }, { 4,  {31,7}  }, { 5,  {31,1}  },
        { 6,  {25,1}  }, { 7,  {19,1}  }, { 8,  {13,1}  }, { 9,  {7,1}   }, { 10, {1,1}   },
        { 11, {1,7}   }, { 12, {1,13}  }, { 13, {1,19}  }, { 14, {1,25}  }, { 15, {1,31}  },
        { 16, {7,31}  }, { 17, {13,31} }, { 18, {19,31} }, { 19, {25,31} }, { 20, {31,31} },
        { 21, {6,6}   }, { 22, {26,6}  }, { 23, {11,11} }, { 24, {21,11} }, { 25, {16,16} },
        { 26, {11,21} }, { 27, {21,21} }, { 28, {6,26}  }, { 29, {26,26} },
    };

    auto position = indexToPositionMap[_Idx];
    position.first -= 1;    position.second -= 1;

    auto pConsoleGraphics = dynamic_cast<ConsoleGraphics*>(pGraph);
    if (nullptr == pConsoleGraphics)
        return;

    pConsoleGraphics->DrawPoint(position.second, position.first, (_Unit & (1 << 0) ? 'a' : _Unit & (1 << 4) ? 'A' : '.'));
    pConsoleGraphics->DrawPoint(position.second, position.first + 1, (_Unit & (1 << 0) ? 'b' : _Unit & (1 << 4) ? 'B' : '.'));
    pConsoleGraphics->DrawPoint(position.second + 1, position.first, (_Unit & (1 << 0) ? 'c' : _Unit & (1 << 4) ? 'C' : '.'));
    pConsoleGraphics->DrawPoint(position.second + 1, position.first + 1, (_Unit & (1 << 0) ? 'd' : _Unit & (1 << 4) ? 'D' : '.'));
}
