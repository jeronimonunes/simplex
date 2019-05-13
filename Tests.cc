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
    Vector ones = Vectors::repeat(1, 4);
    assertEqual(ones.size(), 4);
    for (int i = 0; i < 4; i++)
    {
        assertTrue(ones[i].isOne());
    }
    Vector concat = Vectors::concat(zeros, ones);
    concat = concat * -1;
    assertEqual(concat.size(), 8);
    assertTrue(concat[0].isZero());
    assertTrue(concat[0] == 0);
    assertTrue(concat[7].isNegative());
    assertTrue(concat[7] < 0);
    Vector s = concat * 2;
    assertEqual(s.size(), 8);
    assertTrue(s[0].isZero());
    assertTrue(s[7].isNegative());
    assertTrue(s[7].eval() == -2);

    Fraction f(15, 3);
    assertTrue(f.isPositive());
    assertTrue(f > 0);
    assertTrue(f.eval() == 5);
    assertTrue(!f.isNegative());
    assertTrue(!f.isOne());
    assertTrue(!f.isZero());
    assertTrue((f * Fraction(3, 15)).isOne());
    return 0;
}