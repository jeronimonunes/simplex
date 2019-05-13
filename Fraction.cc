#include "Fraction.hh"
#include <limits>
#include <sstream>
#include "bigint/BigIntegerUtils.hh"
#include <iomanip>

using namespace std;

Fraction::Fraction(BigInteger numerator, BigInteger denominator)
{
    if (numerator == 0L)
    {
        this->numerator = 0L;
        this->denominator = 1L;
    }
    else if (numerator % denominator == 0L)
    {
        this->numerator = numerator / denominator;
        this->denominator = 1L;
    }
    else if (denominator < 0L)
    {
        this->numerator = numerator * -1L;
        this->denominator = denominator * -1L;
    }
    else
    {
        this->numerator = numerator;
        this->denominator = denominator;
    }
}

Fraction::Fraction()
{
    this->numerator = 0;
    this->denominator = 1;
}

Fraction::Fraction(int numerator) : Fraction(BigInteger(numerator), 1)
{
    
}

bool Fraction::isZero() const
{
    return this->numerator == 0L;
}

bool Fraction::isOne() const
{
    return this->numerator != 0L && this->numerator == this->denominator;
}

bool Fraction::isPositive() const
{
    if (this->numerator > 0L && this->denominator > 0L)
        return true;
    if (this->numerator < 0L && this->denominator < 0L)
        return true;
    return false;
}

bool Fraction::isNegative() const
{
    if (this->numerator > 0L && this->denominator < 0L)
        return true;
    if (this->numerator < 0L && this->denominator > 0L)
        return true;
    return false;
}

Fraction Fraction::invert() const
{
    if (this->isZero())
    {
        return 0;
    }
    else
    {
        return Fraction(this->denominator, this->numerator);
    }
}

double toDouble(const BigInteger &v)
{
    stringstream ss;
    ss << v;
    double d;
    ss >> d;
    return d;
}

double Fraction::eval() const
{
    if (this->denominator == 1L)
    {
        return toDouble(this->numerator);
    }
    if (this->numerator == 0L)
    {
        return 0;
    }
    double numerator = toDouble(this->numerator);
    double denominator = toDouble(this->denominator);
    if (denominator == 0)
    {
        return numeric_limits<double>::quiet_NaN();
    }
    return numerator / denominator;
}

bool Fraction::operator<(const Fraction &x) const
{
    if (this->denominator == x.denominator)
    {
        return this->numerator < x.numerator;
    }
    else
    {
        BigInteger a = this->numerator * x.denominator;
        BigInteger b = x.numerator * this->denominator;
        return a < b;
    }
}

Fraction Fraction::operator+(const Fraction v) const
{
    if (isZero())
    {
        return v;
    }
    else if (v.isZero())
    {
        return *this;
    }
    else
    {
        return Fraction(this->numerator * v.denominator + this->denominator * v.numerator, this->denominator * v.denominator);
    }
}

Fraction Fraction::operator*(const Fraction v) const
{
    if (this->isZero() || v.isZero())
    {
        return 0;
    }
    else
    {
        return Fraction(this->numerator * v.numerator, this->denominator * v.denominator);
    }
}

Fraction Fraction::operator/(const Fraction v) const
{
    return (*this) * v.invert();
}

Fraction Fraction::operator-() const
{
    return Fraction(this->numerator * -1, this->denominator);
}

ostream &operator <<(ostream &os, const Fraction &x) {
    cout << setprecision(7) << fixed << x.eval();
    return os;
}