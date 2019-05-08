#ifndef COORDINATE_HH
#define COORDINATE_HH

class Coordinate
{
public:
    int x;
    int y;
    Coordinate(int x, int y);
    bool operator!=(Coordinate &other);
};

extern Coordinate NULL_COORDINATE;

#endif