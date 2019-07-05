#ifndef COORDINATE_HH
#define COORDINATE_HH

#include <iostream>

using namespace std;

class Coordinate
{
public:
    int x;
    int y;
    Coordinate(int x, int y);
    bool isNull() const;
};

std::ostream &operator<<(std::ostream &os, const Coordinate &x);

extern Coordinate NULL_COORDINATE;

#endif