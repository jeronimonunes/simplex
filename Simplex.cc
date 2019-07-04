#include "Simplex.hh"

void runSimplex(Tabloid &firstTabloid, ostream &output)
{
    int auxiliarSteps = 0;

    firstTabloid.fixNegativeB();
    output << "First Tabloid" << endl
           << firstTabloid << endl;

    Tabloid auxiliar = firstTabloid.makeAuxiliarSimplex();

    cout << "Auxiliar: " << auxiliarSteps++ << endl;
    Base auxiliarBase = auxiliar.findBase();
    cout << "Base: " << auxiliarBase << endl;
    cout << auxiliar << endl;

    cout << "Auxiliar: " << auxiliarSteps++ << endl;
    auxiliar = auxiliar.makeBaseUsable(auxiliarBase);
    cout << "Base: " << auxiliarBase << endl;
    Coordinate enter = auxiliar.getCoordinateToEnterBase(auxiliarBase);
    cout << "Enter: (" << enter << ")" << endl;
    cout << auxiliar << endl;

    while (enter != NULL_COORDINATE)
    {
        cout << "BUUUUG" << endl; //TODO print steps
        int leaveIdx = auxiliarBase.findIndexByX(enter.x);
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
        Base base;
        int steps = 0;
        Tabloid tabloid = firstTabloid.continueUsingAuxiliar(auxiliar, auxiliarBase, base);
        cout << "Step: " << steps++ << endl;
        cout << "Base: " << base << endl;
        cout << tabloid << endl;
        tabloid = tabloid.makeBaseUsable(base);
        enter = tabloid.getCoordinateToEnterBase(base);
        cout << "Step: " << steps++ << endl;
        cout << "Base: " << base << endl;
        cout << "Enter: " << enter << endl;
        cout << tabloid << endl;
        while (enter != NULL_COORDINATE)
        {
            int leaveIdx = base.findIndexByX(enter.x);
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