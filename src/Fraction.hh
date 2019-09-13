#ifndef FRACTION_HH
#define FRACTION_HH

#include "../bigint/BigInteger.hh"
#include <iostream>
#include <string>

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
    
    static Fraction fromString(std::string&);

public:
    Fraction();
    Fraction(long i);
    Fraction(BigInteger numerator, BigInteger denominator = 1);

    std::string getNumerator() const;
    std::string getDenominator() const;

    void setNumerator(const std::string& numerator);
    void setDenominator(const std::string& denominator);

    double toDouble() const;

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