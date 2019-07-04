#include "Coordinate.hh"

Coordinate NULL_COORDINATE(-1, -1);

Coordinate::Coordinate(int x, int y)
{
    this->x = x;
    this->y = y;
}

bool Coordinate::operator!=(Coordinate &other)
{
    return this->x != other.x && this->y != other.y;
}

std::ostream &operator<<(std::ostream &os, const Coordinate &v)
{
    return os << v.x << "," << v.y;
}