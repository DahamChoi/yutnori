#pragma once

#include "IGraphics.h"

#include <vector>

class ConsoleGraphics : public IGraphics
{
public:
    void ClearBuffer() override;
    void Draw() override;

public:
    void DrawPoint(int x, int y, char data);
    
private:
    std::vector<std::string> _Buffer;
};