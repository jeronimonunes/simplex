#include "Io.hh"
#include <iostream>
#include <iomanip>

using namespace std;

void print(double value)
{
    cout << setprecision(7) << fixed << value;
}

void print(int value)
{
    print((double) value);
}

void print(const char *str)
{
    cout << str;
}