#ifndef VECTOR_HH
#define VECTOR_HH

#include <vector>
#include "Fraction.hh"

class Vector : public std::vector<Fraction>
{
public:
    explicit Vector();
    explicit Vector(int n);
    explicit Vector(const Fraction frac, int n);
    Vector copy() const;
    Vector concat(const Vector &other) const;

    Vector operator+(const Vector &x) const;
    Vector operator*(const Fraction &x) const;
};

#endif