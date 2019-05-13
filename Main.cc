#include "Vector.hh"
#include "Matrix.hh"
#include "Tabloid.hh"
#include "Matrix.hh"
#include <iostream>

using namespace std;

int findIndex(vector<Coordinate> base, int x)
{
    for (int i = 0; i < base.size(); i++)
    {
        if (base[i].x == x)
            return i;
    }
    return -1; //potential for seg fault
}

int main()
{
    int n, m;
    Matrix A;
    Vector B;
    Vector C;

    cin >> n >> m;

    for (int i = 0; i < m; i++)
    {
        long v;
        cin >> v;
        C.push_back(Fraction(-v));
    }
    for (int i = 0; i < m; i++)
    {
        C.push_back(0);
    }

    while (A.size() < n)
    {
        Vector vector;
        for (int i = 0; i < m; i++)
        {
            long v;
            cin >> v;
            vector.push_back(Fraction(v));
        }
        long b;
        cin >> b;
        bool negative = b < 0L;
        if (negative)
        {
            for (int i = 0; i < m; i++)
            {
                vector[i] = -vector[i];
            }
        }
        //creating auxiliar variables
        for (int i = 0; i < m; i++)
        {
            Fraction v;
            if (i == A.size())
            {
                v = negative ? -1 : 1;
            }
            else
            {
                v = 0;
            }
            vector.push_back(v);
        }
        B.push_back(Fraction(negative ? -b : b));
        A.push_back(vector);
    }

    Tabloid firstTabloid(A, B, C, 0);
    Tabloid auxiliar = firstTabloid.makeAuxiliarSimplex();
    vector<Coordinate> auxiliarBase = auxiliar.findBase();
    auxiliar = auxiliar.makeBaseUsable(auxiliarBase);
    Coordinate enter = auxiliar.getCoordinateToEnterBase(auxiliarBase);
    while (enter != NULL_COORDINATE)
    {
        int leaveIdx = findIndex(auxiliarBase, enter.x);
        auxiliarBase[leaveIdx] = enter;
        auxiliar = auxiliar.makeBaseUsable(auxiliarBase);
        enter = auxiliar.getCoordinateToEnterBase(auxiliarBase);
    }
    if (auxiliar.v.isNegative())
    {
        cout << "inviavel" << endl;
        cout << auxiliar.certificate[0];
        for (int i = 1; i < auxiliar.certificate.size(); i++)
        {
            cout << " " << auxiliar.certificate[i];
        }
        cout << endl;
    }
    else
    {
        vector<Coordinate> base;
        Tabloid tabloid = firstTabloid.continueUsingAuxiliar(auxiliar, auxiliarBase, base);
        tabloid = tabloid.makeBaseUsable(base);
        enter = tabloid.getCoordinateToEnterBase(base);
        while (enter != NULL_COORDINATE)
        {
            int leaveIdx = findIndex(base, enter.x);
            base[leaveIdx] = enter;
            tabloid = tabloid.makeBaseUsable(base);
            enter = tabloid.getCoordinateToEnterBase(base);
        }
        Vector result;
        for (int y = 0; y < tabloid.C.size(); y++)
        {
            Fraction v = tabloid.C[y];
            if (v.isZero())
            {
                bool found = false;
                for (int p = 0; p < base.size(); p++)
                {
                    if (base[p].y == y)
                    {
                        found = true;
                        result.push_back(tabloid.B[base[p].x]);
                    }
                }
                if (!found)
                {
                    result.push_back(0);
                }
            }
            else
            {
                result.push_back(0);
            }
        }
        bool otima = true;
        int negativeColumn = -1;
        for (int g = 0; g < tabloid.C.size(); g++)
        {
            if (tabloid.C[g].isNegative())
            {
                otima = false;
                negativeColumn = g;
                break;
            }
        }
        if (!otima)
        {
            cout << "ilimitada" << endl;
        }
        else
        {
            cout << "otima" << endl;
            cout << tabloid.v << endl;
        }
        cout << result[0];
        for (int i = 1; i < m; i++)
        {
            cout << " " << result[i];
        }
        cout << endl;
        if (otima)
        {
            for (int i = 0; i < tabloid.certificate.size(); i++)
            {
                if (i)
                    cout << " ";
                cout << tabloid.certificate[i];
            }
            cout << endl;
        }
        else
        {
            for (int i = 0; i < m; i++)
            {
                if (i)
                    cout << " ";
                if (tabloid.C[i].isNegative())
                {
                    cout << Fraction(1);
                }
                else
                {
                    Coordinate coord = NULL_COORDINATE;
                    for (int p = 0; p < base.size(); p++)
                    {
                        if (base[p].y == i)
                        {
                            coord = base[p];
                        }
                    }
                    if (coord != NULL_COORDINATE)
                    {
                        cout << -tabloid.A[coord.x][negativeColumn];
                    }
                    else
                    {
                        cout << Fraction(0);
                    }
                }
            }
            cout << endl;
        }
    }
    return 0;
}
