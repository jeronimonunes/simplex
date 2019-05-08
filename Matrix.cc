#include "Matrix.hh"
#include "Vector.hh"

namespace Matrixes
{
Matrix identity(int n)
{
    Matrix result;
    for (int i = 0; i < n; i++)
    {
        Vector line;
        for (int j = 0; j < n; j++)
        {
            if (i == j)
            {
                line.push_back(one);
            }
            else
            {
                line.push_back(zero);
            }
        }
        result.push_back(line);
    }
    return result;
}

Matrix copy(Matrix m)
{
    Matrix result;
    while (result.size() < m.size())
    {
        Vector line = Vectors::copy(m[result.size()]);
        result.push_back(line);
    }
    return result;
}

} // namespace Matrixes