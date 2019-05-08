#ifndef MATRIX_HH
#define MATRIX_HH

#include <vector>
#include "Vector.hh"

typedef std::vector<Vector> Matrix;

namespace Matrixes
{
    Matrix identity(int n);
    Matrix copy(Matrix m);

};

#endif