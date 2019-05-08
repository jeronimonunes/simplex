#ifndef TABLOID_HH
#define TABLOID_HH

#include "Matrix.hh"
#include "Fraction.hh"
#include "Vector.hh"
#include "Coordinate.hh"

class Tabloid
{

public:
    Vector certificate;
    Matrix certificateMatrix;
    Matrix A;
    Vector B;
    Vector C;
    Fraction v;

    Coordinate findBaseColumn(int i);

public:
    Tabloid(Vector certificate, Matrix certificateMatrix, Matrix A, Vector B, Vector C, Fraction v);
    Tabloid makeAuxiliarSimplex();
    std::vector<Coordinate> findBase();
    Tabloid makeBaseUsable(std::vector<Coordinate> base);
    Coordinate getCoordinateToEnterBase(std::vector<Coordinate> base);
    Tabloid continueUsingAuxiliar(Tabloid auxiliar, std::vector<Coordinate> auxiliarBase, std::vector<Coordinate> &output);
};

#endif