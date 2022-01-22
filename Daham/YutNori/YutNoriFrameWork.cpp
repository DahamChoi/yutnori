#include "YutNoriFrameWork.h"

#include <iostream>

#include "Board.h"
#include "ConsolePlayer.h"
#include "ConsoleGraphics.h"

void YutNoriFrameWork::BeginFrameWork()
{
    _pGraphics = std::make_shared<ConsoleGraphics>();
    _pPlayer = std::make_shared<ConsolePlayer>();
    _pBoard = std::make_shared<ConsoleBoard>();
}

void YutNoriFrameWork::EndFrameWork()
{

}

void YutNoriFrameWork::MainWorkImpl()
{
    int N;  std::cin >> N;
    for (int idx = 0; idx < N; idx++)
    {
        auto value = _pPlayer->Input();                   // Input
        _pBoard->Task(value);                              // Update

        // Draw
        _pGraphics->ClearBuffer();
        _pBoard->DrawBoardUnit(_pGraphics.get());
        _pGraphics->Draw();
    }
}

