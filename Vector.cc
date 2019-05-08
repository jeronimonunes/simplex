#include "Vector.hh"
#include "Fraction.hh"

namespace Vectors
{

Vector zeros(int qtd)
{
    return repeat(zero, qtd);
}

Vector repeat(Fraction frac, int qtd)
{
    Vector result;
    while (qtd-- > 0)
        result.push_back(frac);
    return result;
}

Vector copy(Vector other)
{
    Vector result;
    while (result.size() < other.size())
    {
        result.push_back(other[result.size()]);
    }
    return result;
}

Vector concat(Vector a, Vector b)
{
    Vector result;
    while (result.size() < a.size())
    {
        result.push_back(a[result.size()]);
    }
    while (result.size() - a.size() < b.size())
    {
        result.push_back(b[result.size() - a.size()]);
    }
    return result;
}

Vector multiply(Vector a, Fraction b)
{
    Vector result;
    while (result.size() < a.size())
        result.push_back(a[result.size()].multiply(b));
    return result;
}

Vector sum(Vector a, Vector b)
{
    Vector result;
    for (int i = 0; i < a.size() && i < b.size(); i++)
    {
        result.push_back(a[i].add(b[i]));
    }
    return result;
}

} // namespace Vectors