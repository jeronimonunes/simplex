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
  Vector B = this->B;
  Matrix certificateMatrix = this->certificateMatrix;
  for (unsigned int i = 0; i < B.size(); i++)
  {
    if (B[i].isNegative())
    {
      A[i] = -A[i];
      certificateMatrix[i] = -certificateMatrix[i];
      B[i] = -B[i];
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
  Vector C = Vector(this->C.size()).concat(Vector(1, A.size()));
  return Tabloid(certificate, certificateMatrix, A, B, C, 0, base);
}

Tabloid Tabloid::makeBaseUsable() const
{
  Vector certificate = this->certificate;
  Matrix certificateMatrix = this->certificateMatrix;
  Vector C = this->C;
  Matrix A = this->A;
  Vector B = this->B;
  Fraction v = this->v;

  for (const auto &[x, y] : base)
  {
    Vector pline = A[x];
    Vector cpline = certificateMatrix[x];
    if (pline[y].isOne())
    {
      //fine
    }
    else
    {
      Fraction fix = pline[y].invert();
      pline = pline * fix;
      cpline = cpline * fix;
      A[x] = pline;
      certificateMatrix[x] = cpline;
      B[x] = B[x] * fix;
    }
    if (C[y].isZero())
    {
      //fine
    }
    else
    { //fix c
      Fraction fix = -C[y];
      C = C + pline * fix;
      certificate = certificate + cpline * fix;
      v = v + B[x] * fix;
    }
    for (unsigned int i = 0; i < A.size(); i++)
    {
      if (i != x)
      {
        Vector aLine = A[i];
        Vector cLine = certificateMatrix[i];
        if (aLine[y].isZero())
        {
          //fine
        }
        else
        {
          Fraction fix = -aLine[y];
          aLine = aLine + pline * fix;
          cLine = cLine + cpline * fix;
          A[i] = aLine;
          certificateMatrix[i] = cLine;
          B[i] = B[i] + B[x] * fix;
        }
      }
    }
  }

  return Tabloid(certificate, certificateMatrix, A, B, C, v, base);
}

Coordinate Tabloid::getCoordinateToEnterBase() const
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
        return Coordinate(oldIndex, j);
      }
    }
  }
  return NULL_COORDINATE;
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
    if (y >= (int)this->C.size())
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

ostream &operator<<(ostream &os, const Tabloid &x)
{
  os << x.certificate << " | " << x.C << " | " << x.v << endl;
  os << endl;
  for (unsigned int i = 0; i < x.B.size(); i++)
  {
    os << x.certificateMatrix[i] << " | " << x.A[i] << " | " << x.B[i] << endl;
  }
  return os;
}

Tabloid Tabloid::runSimplexStep(bool &stepDone) const
{
  Coordinate enter = getCoordinateToEnterBase();
  if (!enter.isNull())
  {
    stepDone = true;
    Base base = this->base;
    base.remove(enter.x);
    base.set(enter.x, enter.y);
    return Tabloid(certificate, certificateMatrix, A, B, C, v, base);
  }
  else
  {
    stepDone = false;
    return *this;
  }
}
