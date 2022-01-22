#pragma once

#include "FrameWork.h"

#include <memory>

class YutNoriFrameWork : public FrameWork
{
protected:
    virtual void BeginFrameWork();
    virtual void EndFrameWork();

protected:
    virtual void MainWorkImpl();

private:
    std::shared_ptr<class IGraphics> _pGraphics;
    std::shared_ptr<class IPlayer> _pPlayer;
    std::shared_ptr<class Board> _pBoard;
};

