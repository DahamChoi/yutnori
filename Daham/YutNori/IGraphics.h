#pragma once

class IGraphicsObject
{
public:
	virtual void DrawGraphicsObject(class IGraphics* pGraph) = 0;
};

class IGraphics
{
public:
	virtual void ClearBuffer() = 0;
	virtual void Draw() = 0;
};