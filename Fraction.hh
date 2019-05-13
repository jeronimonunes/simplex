#ifndef FRACTION_HH
#define FRACTION_HH

#include "bigint/BigInteger.hh"
#include <iostream>

class Fraction
{

public:
    BigInteger numerator;
    BigInteger denominator;

public:
    Fraction();
    Fraction(int i);
    Fraction(BigInteger numerator, BigInteger denominator = 1);

    bool isOne() const;
    bool isZero() const;
    bool isNegative() const;
    bool isPositive() const;
    bool operator<(const Fraction &x) const;
    Fraction operator+(const Fraction x) const;
    Fraction operator*(const Fraction x) const;
    Fraction operator/(const Fraction x) const;
    Fraction operator-() const;

    Fraction invert() const;

    double eval() const;
};

std::ostream &operator <<(std::ostream &os, const Fraction &x);

#endif