#ifndef FRACTION_HH
#define FRACTION_HH

#include "bigint/BigInteger.hh"
#include <iostream>

class Fraction
{
private:
    BigInteger numerator;
    BigInteger denominator;

public:
    typedef BigInteger::CmpRes CmpRes;
    static const CmpRes
        less = BigInteger::less,
        equal = BigInteger::equal,
        greater = BigInteger::greater;

public:
    Fraction();
    Fraction(long i);
    Fraction(BigInteger numerator, BigInteger denominator = 1);

    bool isOne() const;
    bool isZero() const;
    bool isNegative() const;
    bool isPositive() const;

    CmpRes compareTo(const Fraction &frac) const;

    bool operator==(const Fraction &x) const;
    bool operator!=(const Fraction &x) const;
    bool operator<(const Fraction &x) const;
    bool operator>(const Fraction &x) const;
    bool operator<=(const Fraction &x) const;
    bool operator>=(const Fraction &x) const;

    Fraction operator+(const Fraction &x) const;
    Fraction operator-(const Fraction &x) const;
    Fraction operator*(const Fraction &x) const;
    Fraction operator/(const Fraction &x) const;
    Fraction operator-() const;

    void operator+=(const Fraction &x);
    void operator-=(const Fraction &x);
    void operator*=(const Fraction &x);
    void operator/=(const Fraction &x);

    Fraction invert() const;

    double eval() const;
};

/**
 * outputs this fraction as a decimal number of precision 7
 */
std::ostream &operator<<(std::ostream &os, const Fraction &x);

#endif