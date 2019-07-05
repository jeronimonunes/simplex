#include "Coordinate.hh"

Coordinate NULL_COORDINATE(-1, -1);

Coordinate::Coordinate(int x, int y)
{
    this->x = x;
    this->y = y;
}

bool Coordinate::isNull() const {
    return this->x == -1 && this->y == -1;
}

std::ostream &operator<<(std::ostream &os, const Coordinate &v)
{
    return os << v.x << "," << v.y;
}