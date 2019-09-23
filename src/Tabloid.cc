#include "Tabloid.hh"
#include <limits>
#include <iostream>

Tabloid::Tabloid(
    const Vector &certificate,
    const Matrix &certificateMatrix,
    const Matrix &A,
    const Vector &B,
    const Vector &C,
    const Fraction &v,
    const Base &base)
{
  this->certificate = certificate;
  this->certificateMatrix = certificateMatrix;
  this->A = A;
  this->B = B;
  this->C = C;
  this->v = v;
  this->base = base;
}

Tabloid::Tabloid(
    const Matrix &A,
    const Vector &B,
    const Vector &C,
    const Fraction &v,
    const Base &base) : Tabloid(Vector(B.size()), Matrix(B.size()), A, B, C, v, base)
{
}

Tabloid Tabloid::fixNegativeB() const
{
  Matrix A = this->A;
  Matrix certificateMatrix = this->certificateMatrix;
  Vector B = this->B;
  for (unsigned int i = 0; i < B.size(); i++)
  {
    if (B[i].isNegative())
    {
      A[i].flipSign();
      certificateMatrix[i].flipSign();
      B[i].flipSign();
    }
  }
  return Tabloid(certificate, certificateMatrix, A, B, C, v, base);
}

Tabloid Tabloid::makeAuxiliarSimplex() const
{
  Matrix A = this->A;
  Base base;
  for (unsigned int i = 0; i < this->A.size(); i++)
  {
    for (unsigned int j = 0; j < this->A.size(); j++)
    {
      if (i == j)
      {
        base.set(i, j + this->C.size());
      }
      A[i].push_back(i == j ? 1 : 0);
    }
  }
  const Vector C = Vector(this->C.size()).concat(Vector(1, A.size()));
  return Tabloid(certificate, certificateMatrix, A, B, C, 0, base);
}

Tabloid Tabloid::makeBaseUsable() const
{
  Vector certificate = this->certificate;
  Matrix certificateMatrix = this->certificateMatrix;
  Vector C = this->C;
  Vector B = this->B;
  Matrix A = this->A;
  Fraction v = this->v;

  for (const auto &[x, y] : base)
  {
    Vector &pline = A[x];
    Vector &cpline = certificateMatrix[x];
    if (pline[y].isOne())
    {
      //fine
    }
    else
    {
      Fraction fix = pline[y].invert();
      pline *= fix;
      cpline *= fix;
      B[x] *= fix;
    }
    if (C[y].isZero())
    {
      //fine
    }
    else
    { //fix c
      const Fraction fix = -C[y];
      C += pline * fix;
      certificate += cpline * fix;
      v += B[x] * fix;
    }
    for (unsigned int i = 0; i < A.size(); i++)
    {
      if (i != x)
      {
        Vector &aLine = A[i];
        Vector &cLine = certificateMatrix[i];
        if (aLine[y].isZero())
        {
          //fine
        }
        else
        {
          const Fraction fix = -aLine[y];
          aLine += pline * fix;
          cLine += cpline * fix;
          B[i] += B[x] * fix;
        }
      }
    }
  }

  return Tabloid(certificate, certificateMatrix, A, B, C, v, base);
}

std::pair<int, int> Tabloid::getCoordinateToEnterBase() const
{
  for (unsigned int j = 0; j < this->C.size(); j++)
  {
    if (!base.containsY(j) && this->C[j].isNegative())
    {
      int oldIndex = -1;
      Fraction oldValue;
      for (unsigned int i = 0; i < this->A.size(); i++)
      {
        if (this->A[i][j].isPositive())
        {
          Fraction value = this->B[i] / this->A[i][j];
          if (oldIndex == -1 || value < oldValue)
          {
            oldIndex = i;
            oldValue = value;
          }
        }
      }
      if (oldIndex != -1)
      {
        return {oldIndex, j};
      }
    }
  }
  return {-1, -1};
}

Tabloid Tabloid::continueUsingAuxiliar(const Tabloid &t) const
{
  Base base;
  Matrix A;
  for (unsigned int i = 0; i < t.A.size(); i++)
  {
    Vector line;
    for (unsigned int j = 0; j < this->C.size(); j++)
    {
      line.push_back(t.A[i][j]);
    }
    A.push_back(line);
  }
  for (const auto &[x, y] : t.base)
  {
    if (y >= this->C.size())
    {
      int y = -1;
      for (unsigned int j = 0; j < A[x].size(); j++)
      {
        Fraction column = A[x][j];
        if (!column.isZero())
        {
          y = j;
        }
      }
      if (y >= 0)
      {
        base.set(x, y);
      }
    }
    else
    {
      base.set(x, y);
    }
  }
  return Tabloid(Vector(A.size()), t.certificateMatrix, A, t.B, this->C, 0, base);
}

std::ostream &operator<<(std::ostream &os, const Tabloid &x)
{
  os << x.certificate << " | " << x.C << " | " << x.v << std::endl;
  os << std::endl;
  for (unsigned int i = 0; i < x.B.size(); i++)
  {
    os << x.certificateMatrix[i] << " | " << x.A[i] << " | " << x.B[i] << std::endl;
  }
  return os;
}

Tabloid Tabloid::runSimplexStep(bool &stepDone) const
{
  const auto [x, y] = getCoordinateToEnterBase();
  if (x != -1 && y != -1)
  {
    stepDone = true;
    Base base = this->base;
    base.remove(x);
    base.set(x, y);
    return Tabloid(certificate, certificateMatrix, A, B, C, v, base);
  }
  else
  {
    stepDone = false;
    return *this;
  }
}
