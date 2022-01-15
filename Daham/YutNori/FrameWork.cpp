#include "FrameWork.h"

void FrameWork::MainWorkFrameWork()
{
    BeginFrameWork();
    MainWorkImpl();
    EndFrameWork();
}
