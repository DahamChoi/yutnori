#pragma once

namespace Task
{
    struct GameInputValue
    {
        char type;
        int force;
    };
}

class ITask
{
public:
    virtual void Task(const Task::GameInputValue& gameInputValue) = 0;
};

class IBoard
{
public:
    virtual void DrawBoardUnit(IGraphics* pGraphics) = 0;
};