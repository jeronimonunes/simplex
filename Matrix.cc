#include "Matrix.hh"
#include "Vector.hh"

Matrix::Matrix()
{
}

Matrix::Matrix(int n)
{
    for (int i = 0; i < n; i++)
    {
        Vector line;
        for (int j = 0; j < n; j++)
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

Matrix Matrix::copy() const
{
    Matrix result;
    while (result.size() < this->size())
    {
        Vector line = this->at(result.size()).copy();
        result.push_back(line);
    }
    return result;
}

Vector operator*(Vector &a, Matrix &b)
{
    Vector result;
    for (int j = 0; j < b[0].size(); j++)
    {
        Fraction sum;
        for (int i = 0; i < a.size(); i++)
        {
            sum += b[i][j] * a[i];
        }
        result.push_back(sum);
    }
    return result;
}