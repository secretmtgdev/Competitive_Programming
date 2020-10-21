#include "SkylinePoint.h"

SkylinePoint::SkylinePoint(int xPosition, int xHeight, bool isStart)
{
    _xPosition = xPosition;
    _xHeight = xHeight;
    _isStart = isStart;
}

int SkylinePoint::getX()
{
    return _xPosition;
}

int SkylinePoint::getHeight()
{
    return _xHeight;
}

bool SkylinePoint::isStart()
{
    return _isStart;
}