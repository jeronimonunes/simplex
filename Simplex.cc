#include "Simplex.hh"

int findIndex(vector<Coordinate> base, int x)
{
    for (int i = 0; i < base.size(); i++)
    {
        if (base[i].x == x)
            return i;
    }
    return -1; //potential for seg fault
}

void runSimplex(
    Vector &certificate,
    Matrix &certificateMatrix,
    Matrix &A,
    Vector &B,
    Vector &C,
    Fraction &v)
{
    Tabloid firstTabloid(certificate, certificateMatrix, A, B, C, 0);
    firstTabloid.fixNegativeB();
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
        cout << auxiliar.certificate << endl;
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
        cout << result << endl;
        if (otima)
        {
            cout << tabloid.certificate << endl;
        }
        else
        {
            for (int i = 0; i < tabloid.C.size(); i++)
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
}