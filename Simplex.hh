#ifndef SIMPLEX_HH
#define SIMPLEX_HH
#include "Vector.hh"
#include "Matrix.hh"
#include "Tabloid.hh"
#include "Matrix.hh"

void runSimplex(
    Vector &certificate,
    Matrix &certificateMatrix,
    Matrix &A,
    Vector &B,
    Vector &C,
    Fraction &v);

#endif