#include "Matrix.hh"
#include "Vector.hh"

Matrix::Matrix()
{
}

Matrix::Matrix(unsigned int n)
{
    for (unsigned int i = 0; i < n; i++)
    {
        Vector line;
        for (unsigned int j = 0; j < n; j++)
        {
            if (i == j)
            {
                line.push_back(1);
            }
            else
            {
                line.push_back(0);
            }
        }
        this->push_back(line);
    }
}

Vector operator*(Vector &a, Matrix &b)
{
    Vector result;
    for (unsigned int j = 0; j < b[0].size(); j++)
    {
        Fraction sum;
        for (unsigned int i = 0; i < a.size(); i++)
        {
            sum += b[i][j] * a[i];
        }
        result.push_back(sum);
    }
    return result;
}