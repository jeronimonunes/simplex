#ifndef TABLOID_HH
#define TABLOID_HH

#include "Matrix.hh"
#include "Fraction.hh"
#include "Vector.hh"
#include "Coordinate.hh"
#include "Base.hh"

class Tabloid
{

public:
    Vector certificate;
    Matrix certificateMatrix;
    Matrix A;
    Vector B;
    Vector C;
    Fraction v;

    Coordinate findBaseColumn(unsigned int i) const;

public:
    Tabloid(Vector certificate, Matrix certificateMatrix, Matrix A, Vector B, Vector C, Fraction v);
    Tabloid(Matrix A, Vector B, Vector C, Fraction v = 0);
    void fixNegativeB();
    Tabloid makeAuxiliarSimplex() const;
    Base findBase() const;
    Tabloid makeBaseUsable(const Base &base) const;
    Coordinate getCoordinateToEnterBase(const Base &base) const;
    Tabloid continueUsingAuxiliar(Tabloid auxiliar, const Base &auxiliarBase, Base &output) const;
};

std::ostream &operator<<(std::ostream &os, const Tabloid &x);

#endif