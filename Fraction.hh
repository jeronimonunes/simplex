#ifndef FRACTION_HH
#define FRACTION_HH

class Fraction
{

public:
    long numerator;
    long denominator;

public:
    Fraction();
    Fraction(long numerator);
    Fraction(long numerator, long denominator);
    Fraction multiply(Fraction f);
    Fraction divide(Fraction f);
    Fraction add(Fraction f);

    bool isOne();
    bool isZero();
    bool isNegative();
    bool isPositive();

    Fraction invert();

    double eval();
};

extern Fraction zero;
extern Fraction one;
extern Fraction neg;

#endif