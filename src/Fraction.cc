#include "Fraction.hh"
#include <sstream>
#include "../bigint/BigIntegerUtils.hh"
#include "StringUtil.hh"
#include <iomanip>

using namespace std;

BigInteger gcd(const BigInteger &a, const BigInteger &b)
{
  if (b == 0)
    return a;
  return gcd(b, a % b);
}

double bigIntegerToDouble(const BigInteger &v)
{
  return stod(bigIntegerToString(v));
}

Fraction Fraction::fromString(const string &s)
{
  vector<string> parts = explode(s, {'/'});
  if (parts.size() == 1)
  {
    return stringToBigInteger(parts[0]);
  }
  else
  {
    BigInteger numerator = stringToBigInteger(parts[0]);
    BigInteger denominator = stringToBigInteger(parts[1]);
    return Fraction(numerator, denominator);
  }
}

Fraction::Fraction(BigInteger numerator, BigInteger denominator)
{
  if (numerator == 0)
  {
    this->numerator = 0;
    this->denominator = 1;
  }
  else
  {
    if (denominator < 0)
    {
      numerator *= -1;
      denominator *= -1;
    }
    BigInteger gcdv = gcd(numerator, denominator);
    this->numerator = numerator / gcdv;
    this->denominator = denominator / gcdv;
  }
}

Fraction::Fraction()
{
  this->numerator = 0;
  this->denominator = 1;
}

Fraction::Fraction(long numerator)
{
  this->numerator = numerator;
  this->denominator = 1;
}

std::string Fraction::getNumerator() const
{
  return bigIntegerToString(this->numerator);
}

std::string Fraction::getDenominator() const
{
  return bigIntegerToString(this->denominator);
}

void Fraction::setNumerator(const std::string &numerator)
{
  this->numerator = stringToBigInteger(numerator);
}

void Fraction::setDenominator(const std::string &denominator)
{
  this->denominator = stringToBigInteger(denominator);
}

double Fraction::toDouble() const
{
  double n = bigIntegerToDouble(this->numerator);
  double d = bigIntegerToDouble(this->denominator);
  return n / d;
}

bool Fraction::isZero() const
{
  return this->numerator == 0;
}

bool Fraction::isOne() const
{
  return this->numerator != 0 && this->numerator == this->denominator;
}

bool Fraction::isPositive() const
{
  if (this->numerator > 0 && this->denominator > 0)
    return true;
  if (this->numerator < 0 && this->denominator < 0)
    return true;
  return false;
}

bool Fraction::isNegative() const
{
  if (this->numerator > 0 && this->denominator < 0)
    return true;
  if (this->numerator < 0 && this->denominator > 0)
    return true;
  return false;
}

Fraction::CmpRes Fraction::compareTo(const Fraction &frac) const
{
  if (this->denominator == frac.denominator)
  {
    return this->numerator.compareTo(frac.numerator);
  }
  else
  {
    BigInteger a = this->numerator * frac.denominator;
    BigInteger b = frac.numerator * this->denominator;
    return a.compareTo(b);
  }
}

bool Fraction::operator==(const Fraction &x) const
{
  return this->compareTo(x) == Fraction::equal;
}

bool Fraction::operator!=(const Fraction &x) const
{
  return this->compareTo(x) != Fraction::equal;
}

bool Fraction::operator<(const Fraction &x) const
{
  return this->compareTo(x) == Fraction::less;
}

bool Fraction::operator>(const Fraction &x) const
{
  return this->compareTo(x) == Fraction::greater;
}

bool Fraction::operator<=(const Fraction &x) const
{
  return this->compareTo(x) != Fraction::greater;
}

bool Fraction::operator>=(const Fraction &x) const
{
  return this->compareTo(x) != Fraction::less;
}

Fraction Fraction::operator+(const Fraction &v) const
{
  return Fraction(this->numerator * v.denominator + this->denominator * v.numerator, this->denominator * v.denominator);
}

Fraction Fraction::operator-(const Fraction &v) const
{
  return *this + -v;
}

Fraction Fraction::operator*(const Fraction &v) const
{
  return Fraction(this->numerator * v.numerator, this->denominator * v.denominator);
}

Fraction Fraction::operator/(const Fraction &v) const
{
  return (*this) * v.invert();
}

Fraction Fraction::operator-() const
{
  return Fraction(this->numerator * -1, this->denominator);
}

void Fraction::operator+=(const Fraction &x)
{
  (*this) = (*this) + x;
}

void Fraction::operator-=(const Fraction &x)
{
  (*this) = (*this) - x;
}

void Fraction::operator*=(const Fraction &x)
{
  (*this) = (*this) * x;
}

void Fraction::operator/=(const Fraction &x)
{
  (*this) = (*this) / x;
}

Fraction Fraction::invert() const
{
  //TODO maybe should throw an error
  if ((*this) == 0)
    return 0;
  else
    return Fraction(this->denominator, this->numerator);
}

void Fraction::flipSign()
{
  if ((*this) == 0)
    return;
  else
    this->numerator.flipSign();
}

ostream &operator<<(ostream &os, const Fraction &x)
{
  os << std::setprecision(7) << x.toDouble();
  return os;
}
