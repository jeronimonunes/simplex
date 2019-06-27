# Simplex C++ Engine

This is a implementation of the simplex algorithm written in C++, the calculations are all made with infinite precision by using an internal Fraction implementation that uses biginteger as its numerator and denominator values.

## Usage

The input of this program should be a Tabloid, already in FPI form, example:

```
0 0 0 0 | 3 4 -5  5 0  0 0  0 |  0
--------+---------------------+---
1 0 0 0 | 1 1  0  0 1  0 0  0 |  5
0 1 0 0 | 1 0  5 -5 0 -1 0  0 | 10
0 0 1 0 | 2 1  1 -1 0  0 1  0 | 10
0 0 0 1 | 2 1  1 -1 0  0 0 -1 | 10
```

Multiple spaces are ignored, the numbers must be integers or fractions. If they are fractions you must use '/'. Ex.: -15/3.
The second line will be ignored, no matter what it contains.

The program will output multiple tabloids on the same format as above until the simplex finishes, if it does.
