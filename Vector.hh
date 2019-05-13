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
}; // namespace Vectors

Vector operator+(Vector &a, Vector &b);
Vector operator+(Vector &a, Vector b);
Vector operator*(Vector &a, Fraction &b);
Vector operator*(Vector &a, int b);

#endif