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
  Tabloid(
      const Vector &certificate,
      const Matrix &certificateMatrix,
      const Matrix &A,
      const Vector &B,
      const Vector &C,
      const Fraction &v);
  Tabloid(
      const Matrix &A,
      const Vector &B,
      const Vector &C,
      const Fraction &v = 0);
  Tabloid fixNegativeB() const;
  Tabloid makeAuxiliarSimplex() const;
  Base findBase() const;
  Tabloid makeBaseUsable(const Base &base) const;
  Coordinate getCoordinateToEnterBase(const Base &base) const;
  Tabloid continueUsingAuxiliar(const Tabloid &auxiliar, const Base &auxiliarBase, Base &output) const;
};

std::ostream &operator<<(std::ostream &os, const Tabloid &x);

#endif