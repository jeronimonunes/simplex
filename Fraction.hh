#ifndef FRACTION_HH
#define FRACTION_HH

#include "bigint/BigInteger.hh"
#include <iostream>
#include <string>

using namespace std;

class Fraction
{
public:
    BigInteger numerator;
    BigInteger denominator;

public:
    typedef BigInteger::CmpRes CmpRes;
    static const CmpRes
        less = BigInteger::less,
        equal = BigInteger::equal,
        greater = BigInteger::greater;
    
    static Fraction fromString(string&);

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
};

std::ostream &operator<<(std::ostream &os, const Fraction &x);

#endif