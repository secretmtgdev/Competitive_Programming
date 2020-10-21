#include "Point.h"

Point::Point(int r, int c)
{
    row = r;
    col = c;
}

void Point::setRow(int r)
{
    row = r;
}

void Point::setCol(int c)
{
    col = c;
}

int Point::getRow()
{
    return row;
}

int Point::getCol()
{
    return col;
}