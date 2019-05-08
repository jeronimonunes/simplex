#include "Fraction.hh"
#include <limits>

Fraction zero(0L);
Fraction one(1L);
Fraction neg(-1L);

Fraction::Fraction(long numerator, long denominator)
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
    this->numerator = 0L;
    this->denominator = 1L;
}

Fraction::Fraction(long numerator)
{
    this->numerator = numerator;
    this->denominator = 1L;
}

Fraction Fraction::multiply(Fraction v)
{
    Fraction result(this->numerator * v.numerator, this->denominator * v.denominator);
    return result;
}

Fraction Fraction::divide(Fraction v)
{
    return this->multiply(v.invert());
}

Fraction Fraction::add(Fraction v)
{
    Fraction result(this->numerator * v.denominator + this->denominator * v.numerator, this->denominator * v.denominator);
    return result;
}

bool Fraction::isZero()
{
    return this->numerator == 0L;
}

bool Fraction::isOne()
{
    return this->numerator != 0L && this->numerator == this->denominator;
}

bool Fraction::isPositive()
{
    if (this->numerator > 0L && this->denominator > 0L)
        return true;
    if (this->numerator < 0L && this->denominator < 0L)
        return true;
    return false;
}

bool Fraction::isNegative()
{
    if (this->numerator > 0L && this->denominator < 0L)
        return true;
    if (this->numerator < 0L && this->denominator > 0L)
        return true;
    return false;
}

Fraction Fraction::invert()
{
    return Fraction(this->denominator, this->numerator);
}

double Fraction::eval()
{
    if(this->denominator == 1L) {
        return this->numerator;
    }
    if(this->numerator == 0L) {
        return 0;
    }
    double numerator = this->numerator;
    double denominator = this->denominator;
    if(denominator == 0) {
        return std::numeric_limits<double>::quiet_NaN();
    }
    return numerator / denominator;
}