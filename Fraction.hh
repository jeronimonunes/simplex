#ifndef FRACTION_HH
#define FRACTION_HH

#include "bigint/BigInteger.hh"

class Fraction
{

public:
    BigInteger numerator;
    BigInteger denominator;

public:
    Fraction();
    Fraction(BigInteger numerator);
    Fraction(BigInteger numerator, BigInteger denominator);
    Fraction multiply(Fraction f);
    Fraction divide(Fraction f);
    Fraction add(Fraction f);

    bool isOne();
    bool isZero();
    bool isNegative();
    bool isPositive();
    bool operator < (const Fraction &x) const ;

    Fraction invert();

    double eval();
};

extern Fraction zero;
extern Fraction one;
extern Fraction neg;

#endif