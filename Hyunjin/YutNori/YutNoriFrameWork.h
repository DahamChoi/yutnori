#pragma once

#include "FrameWork.h"

#include "Board.h"
#include "Player.h"
#include "Map.h"

class YutNoriFrameWork : public FrameWork
{
protected:
	virtual void BeginFrameWork();
	virtual void EndFrameWork();

protected:
	virtual void MainWorkImpl();

private:
	Board _Board;
	Player _Player;
	Map _Map;
};

