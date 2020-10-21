class SkylinePoint
{
    int _xPosition, _xHeight;
    bool _isStart;

public:
    SkylinePoint(int, int, bool);
    int getX();
    int getHeight();
    bool isStart();
};