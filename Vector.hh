#ifndef VECTOR_HH
#define VECTOR_HH

#include <vector>
#include "Fraction.hh"

typedef std::vector<Fraction> Vector;

namespace Vectors
{
Vector copy(Vector v);
Vector zeros(int n);
Vector repeat(Fraction frac, int n);
Vector concat(Vector a, Vector b);
Vector multiply(Vector a, Fraction b);
Vector sum(Vector a, Vector b);
}; // namespace Vectors

#endif