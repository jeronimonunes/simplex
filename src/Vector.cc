#include "Vector.hh"
#include "Fraction.hh"

Vector::Vector()
{
}

// Create a vector with n positions filled with frac
Vector::Vector(Fraction frac, int n)
{
    while (n-- > 0)
        this->push_back(frac);
}

// Create a zero vector with n positions
Vector::Vector(int n) : Vector(0, n)
{
}

Vector Vector::copy() const
{
    Vector result;
    while (result.size() < this->size())
    {
        result.push_back(this->at(result.size()));
    }
    return result;
}

Vector Vector::concat(const Vector &b) const
{
    Vector result;
    while (result.size() < this->size())
    {
        result.push_back(this->at(result.size()));
    }
    while (result.size() - this->size() < b.size())
    {
        result.push_back(b[result.size() - this->size()]);
    }
    return result;
}

Vector Vector::operator+(const Vector &b) const
{
    Vector result;
    for (int i = 0; i < this->size() && i < b.size(); i++)
    {
        result.push_back(this->at(i) + b[i]);
    }
    return result;
}

Vector Vector::operator*(const Fraction &b) const
{
    Vector result;
    while (result.size() < this->size())
        result.push_back(this->at(result.size()) * b);
    return result;
}

Fraction Vector::operator*(const Vector &x) const
{
    Fraction result;
    for (int i = 0; i < this->size() && i < x.size(); i++)
    {
        result += this->at(i) * x[i];
    }
    return result;
}

Vector Vector::operator-() const
{
    Vector result;
    for (int i = 0; i < this->size(); i++)
    {
        result.push_back(-this->at(i));
    }
    return result;
}

std::ostream &operator<<(std::ostream &os, const Vector &x)
{
    if (x.size() > 0)
    {
        os << x[0];
        for (int i = 1; i < x.size(); i++)
        {
            os << " " << x[i];
        }
    }
    return os;
}