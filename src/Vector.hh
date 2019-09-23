#ifndef VECTOR_HH
#define VECTOR_HH

#include <vector>
#include "Fraction.hh"

class Vector : public std::vector<Fraction>
{
public:
  explicit Vector();
  explicit Vector(unsigned int n);
  explicit Vector(const Fraction frac, int n);
  Vector crop(unsigned int n) const;
  Vector concat(const Vector &other) const;

  Vector operator+(const Vector &x) const;
  Vector operator*(const Fraction &x) const;
  Fraction operator*(const Vector &x) const;
  Vector operator-() const;

  void flipSign();

  void operator+=(const Vector &x);
  void operator*=(const Fraction &x);
};

std::ostream &operator<<(std::ostream &os, const Vector &x);

#endif
