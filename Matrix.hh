#ifndef MATRIX_HH
#define MATRIX_HH

#include <vector>
#include "Vector.hh"

class Matrix : public std::vector<Vector>
{

public:
    Matrix();
    //creates an identity matrix of size n * n
    Matrix(int n);
    Matrix copy() const;
};

#endif