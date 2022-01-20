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
	int N;	std::cin >> N;
	for (int idx = 0; idx < N; idx++)
	{
		auto value = _Player.Input();
		_Board.Task(value);

		_Map.ClearBuffer();

		const auto& vecNode = _Board.GetVecNode();
		_Map.AddUnitBuffer(vecNode);

		_Map.Draw();
	}
}
