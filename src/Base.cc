#include "Base.hh"

bool Base::containsY(int y) const
{
    for (unsigned int i = 0; i < this->size(); i++)
    {
        if ((*this)[i].y == y)
            return true;
    }
    return false;
}

int Base::findIndexByX(int x) const
{
    for (unsigned int i = 0; i < this->size(); i++)
    {
        if ((*this)[i].x == x)
            return i;
    }
    return -1; //potential for seg fault
}

std::ostream &operator<<(std::ostream &os, const Base &v)
{
    if (v.size() > 0)
    {
        os << "(" << v[0] << ")";
        for (unsigned int i = 1; i < v.size(); i++)
        {
            os << " (" << v[i] << ")";
        }
    }
    return os;
}