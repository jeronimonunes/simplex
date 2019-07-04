#ifndef BASE_HH
#define BASE_HH

#include <vector>
#include "Coordinate.hh"
#include <ostream>

class Base : public std::vector<Coordinate>
{
public:
    bool containsY(int y) const;
    int findIndexByX(int x) const;
};

std::ostream &operator<<(std::ostream &os, const Base &x);

#endif