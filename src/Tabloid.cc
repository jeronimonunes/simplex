#include "Tabloid.hh"
#include <limits>
#include <iostream>

Tabloid::Tabloid(Vector certificate, Matrix certificateMatrix, Matrix A, Vector B, Vector C, Fraction v)
{
    this->certificate = certificate;
    this->certificateMatrix = certificateMatrix;
    this->A = A;
    this->B = B;
    this->C = C;
    this->v = v;
}

Tabloid::Tabloid(Matrix A, Vector B, Vector C, Fraction v) : Tabloid(Vector(B.size()), Matrix(B.size()), A, B, C, v)
{
}

void Tabloid::fixNegativeB()
{
    for (unsigned int i = 0; i < this->B.size(); i++)
    {
        if (B[i].isNegative())
        {
            this->A[i] = -this->A[i];
            this->certificateMatrix[i] = -this->certificateMatrix[i];
            B[i] = -B[i];
        }
    }
}

Tabloid Tabloid::makeAuxiliarSimplex() const
{
    Matrix A = this->A.copy();
    for (unsigned int i = 0; i < this->A.size(); i++)
    {
        for (unsigned int j = 0; j < this->A.size(); j++)
        {
            A[i].push_back(i == j ? 1 : 0);
        }
    }
    Vector C = Vector(this->C.size()).concat(Vector(1, A.size()));
    return Tabloid(this->certificate, this->certificateMatrix, A, this->B, C, 0);
}

Base Tabloid::findBase() const
{
    Base result;
    for (unsigned int i = 0; i < this->A.size(); i++)
    {
        result.push_back(this->findBaseColumn(i));
    }
    return result;
}

Coordinate Tabloid::findBaseColumn(unsigned int idx) const
{
    for (unsigned int j = 0; j < this->C.size(); j++)
    {
        bool ok = true;
        for (unsigned int i = 0; i < this->A.size(); i++)
        {
            if (i == idx)
            {
                ok = this->A[i][j].isOne();
            }
            else
            {
                ok = this->A[i][j].isZero();
            }
            if (!ok)
                break;
        }
        if (ok)
            return Coordinate(idx, j);
    }
    return NULL_COORDINATE;
}

Tabloid Tabloid::makeBaseUsable(const Base& base) const
{
    Vector certificate = this->certificate.copy();
    Matrix certificateMatrix = this->certificateMatrix.copy();
    Vector C = this->C.copy();
    Matrix A = this->A.copy();
    Vector B = this->B.copy();
    Fraction v = this->v;

    for (unsigned int u = 0; u < base.size(); u++)
    {
        Coordinate coord = base[u];
        Vector pline = A[coord.x];
        Vector cpline = certificateMatrix[coord.x];
        if (pline[coord.y].isOne())
        {
            //fine
        }
        else
        {
            Fraction fix = pline[coord.y].invert();
            pline = pline * fix;
            cpline = cpline * fix;
            A[coord.x] = pline;
            certificateMatrix[coord.x] = cpline;
            B[coord.x] = B[coord.x] * fix;
        }
        if (C[coord.y].isZero())
        {
            //fine
        }
        else
        { //fix c
            Fraction fix = -C[coord.y];
            C = C + pline * fix;
            certificate = certificate + cpline * fix;
            v = v + B[coord.x] * fix;
        }
        for (unsigned int i = 0; i < A.size(); i++)
        {
            if ((int)i != coord.x)
            {
                Vector aLine = A[i];
                Vector cLine = certificateMatrix[i];
                if (aLine[coord.y].isZero())
                {
                    //fine
                }
                else
                {
                    Fraction fix = -aLine[coord.y];
                    aLine = aLine + pline * fix;
                    cLine = cLine + cpline * fix;
                    A[i] = aLine;
                    certificateMatrix[i] = cLine;
                    B[i] = B[i] + B[coord.x] * fix;
                }
            }
        }
    }

    return Tabloid(certificate, certificateMatrix, A, B, C, v);
}

Coordinate Tabloid::getCoordinateToEnterBase(const Base &base) const
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

Tabloid Tabloid::continueUsingAuxiliar(Tabloid t, const Base& auxiliarBase, Base &output) const
{
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
    for (unsigned int i = 0; i < auxiliarBase.size(); i++)
    {
        Coordinate coord = auxiliarBase[i];
        if (coord.y >= (int)this->C.size())
        {
            int y = -1;
            for (unsigned int j = 0; j < A[coord.x].size(); j++)
            {
                Fraction column = A[coord.x][j];
                if (!column.isZero())
                {
                    y = j;
                }
            }
            if (y >= 0)
            {
                output.push_back(Coordinate(coord.x, y));
            }
            else
            {
                //potential for seg fault
                output.push_back(NULL_COORDINATE);
            }
        }
        else
        {
            output.push_back(coord);
        }
    }
    return Tabloid(Vector(A.size()), t.certificateMatrix, A, t.B, this->C, 0);
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