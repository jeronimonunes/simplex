#include "Vector.hh"

#include <iostream>

using namespace std;

void assertTrue(bool b)
{
    if (b)
    {
        cout << "ok" << endl;
    }
    else
    {
        cerr << "error" << endl;
    }
}

void assertEqual(int a, int b)
{
    assertTrue(a == b);
}

int main()
{
    Vector zeros = Vectors::zeros(4);
    assertEqual(zeros.size(), 4);
    for (int i = 0; i < 4; i++)
    {
        assertTrue(zeros[i].isZero());
    }
    Vector ones = Vectors::repeat(one, 4);
    assertEqual(ones.size(), 4);
    for (int i = 0; i < 4; i++)
    {
        assertTrue(ones[i].isOne());
    }
    Vector concat = Vectors::concat(zeros, ones);
    concat = Vectors::multiply(concat, neg);
    assertEqual(concat.size(), 8);
    assertTrue(concat[0].isZero());
    assertTrue(concat[7].isNegative());
    Vector s = Vectors::sum(concat, concat);
    assertEqual(s.size(), 8);
    assertTrue(s[0].isZero());
    assertTrue(s[7].isNegative());
    assertTrue(s[7].eval() == one.add(one).multiply(neg).eval());

    Fraction f(15, 3);
    assertTrue(f.isPositive());
    assertTrue(f.eval() == 5);
    assertTrue(!f.isNegative());
    assertTrue(!f.isOne());
    assertTrue(!f.isZero());
    assertTrue(f.multiply(Fraction(3, 15)).isOne());
    return 0;
}