#include "point.h"

point::point(int r, int c)
{
    row = r;
    col = c;
}

void point::setRow(int r)
{
    row = r;
}

void point::setCol(int c)
{
    col = c;
}

int point::getRow()
{
    return row;
}

int point::getCol()
{
    return col;
}