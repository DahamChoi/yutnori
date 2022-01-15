#include "YutNoriFrameWork.h"

void YutNoriFrameWork::BeginFrameWork()
{
	_Board.Init();
}

void YutNoriFrameWork::EndFrameWork()
{

}

void YutNoriFrameWork::MainWorkImpl()
{
    int N;  std::cin >> N;
    for (int idx = 0; idx < N; idx++)
    {
        auto value = _Player.Input();                   // Input
        _Board.Task(value);                             // Update

        // Draw
        _Map.ClearBuffer();

        for (int idx = 1; idx < 30; idx++)
        {
            const auto& pNode = _Board.GetNode(idx);
            _Map.AddUnitBuffer(pNode);
        }

        _Map.Draw();
    }
}

