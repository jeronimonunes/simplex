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

Tabloid Tabloid::makeAuxiliarSimplex()
{
    Matrix A = this->A.copy();
    for (int i = 0; i < this->A.size(); i++)
    {
        for (int j = 0; j < this->A.size(); j++)
        {
            A[i].push_back(i == j ? 1 : 0);
        }
    }
    Vector C = Vector(this->C.size()).concat(Vector(1, A.size()));
    return Tabloid(this->certificate, this->certificateMatrix, A, this->B, C, 0);
}

std::vector<Coordinate> Tabloid::findBase()
{
    std::vector<Coordinate> result;
    for (int i = 0; i < this->A.size(); i++)
    {
        result.push_back(this->findBaseColumn(i));
    }
    return result;
}

Coordinate Tabloid::findBaseColumn(int idx)
{
    for (int j = 0; j < this->C.size(); j++)
    {
        bool ok = true;
        for (int i = 0; i < this->A.size(); i++)
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

Tabloid Tabloid::makeBaseUsable(std::vector<Coordinate> base)
{
    Vector certificate = this->certificate.copy();
    Matrix certificateMatrix = this->certificateMatrix.copy();
    Vector C = this->C.copy();
    Matrix A = this->A.copy();
    Vector B = this->B.copy();
    Fraction v = this->v;

    for (int u = 0; u < base.size(); u++)
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
        for (int i = 0; i < A.size(); i++)
        {
            if (i != coord.x)
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

bool find(std::vector<Coordinate> base, int j)
{
    for (int i = 0; i < base.size(); i++)
    {
        if (base[i].y == j)
            return true;
    }
    return false;
}

Coordinate Tabloid::getCoordinateToEnterBase(std::vector<Coordinate> base)
{
    for (int j = 0; j < this->C.size(); j++)
    {
        if (!find(base, j) && this->C[j].isNegative())
        {
            int oldIndex = -1;
            Fraction oldValue;
            for (int i = 0; i < this->A.size(); i++)
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

Tabloid Tabloid::continueUsingAuxiliar(Tabloid t, std::vector<Coordinate> auxiliarBase, std::vector<Coordinate> &output)
{
    Matrix A;
    for (int i = 0; i < t.A.size(); i++)
    {
        Vector line;
        for (int j = 0; j < this->C.size(); j++)
        {
            line.push_back(t.A[i][j]);
        }
        A.push_back(line);
    }
    for (int i = 0; i < auxiliarBase.size(); i++)
    {
        Coordinate coord = auxiliarBase[i];
        if (coord.y >= this->C.size())
        {
            int y = -1;
            for (int j = 0; j < A[coord.x].size(); j++)
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