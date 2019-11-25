#ifndef TABLOID_HH
#define TABLOID_HH

#include "Matrix.hh"
#include "Fraction.hh"
#include "Vector.hh"
#include "Base.hh"

enum class ResultType
{
  INFEASIBLE,
  ILIMITED,
  LIMITED
};

class Result
{
public:
  ResultType type;
  Vector certificate;
  Fraction value;
  Vector solution;
};

class Tabloid
{

public:
  Vector certificate;
  Matrix certificateMatrix;
  Matrix A;
  Vector B;
  Vector C;
  Fraction v;
  Base base;

private:
  std::pair<int, int> getCoordinateToEnterBase() const;

public:
  Tabloid(
      const Vector &certificate,
      const Matrix &certificateMatrix,
      const Matrix &A,
      const Vector &B,
      const Vector &C,
      const Fraction &v,
      const Base &base);
  Tabloid(
      const Matrix &A,
      const Vector &B,
      const Vector &C,
      const Fraction &v = 0,
      const Base &base = Base());
  Tabloid fixNegativeB() const;
  Tabloid makeAuxiliarSimplex() const;
  Tabloid makeBaseUsable() const;
  Tabloid continueUsingAuxiliar(const Tabloid &auxiliar) const;
  Tabloid runSimplexStep(bool &stepDone) const;
  Result getResult() const;
};

std::ostream &operator<<(std::ostream &os, const Tabloid &x);

#endif
