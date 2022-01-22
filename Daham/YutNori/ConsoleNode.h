#pragma once

#include "IGraphics.h"
#include "Node.h"

class ConsoleNode : public node, public IGraphicsObject
{
public:
	virtual void DrawGraphicsObject(class IGraphics* pGraph) override;
};
