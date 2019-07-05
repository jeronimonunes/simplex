#include "Simplex.hh"

void runSimplex(Tabloid &firstTabloid, ostream *stepsOutput, ostream &resultOutput)
{
    int auxiliarSteps = 0;

    firstTabloid.fixNegativeB();
    if (stepsOutput)
    {
        *stepsOutput << "First Tabloid" << endl
               << firstTabloid << endl;
    }

    Tabloid auxiliar = firstTabloid.makeAuxiliarSimplex();

    Base auxiliarBase = auxiliar.findBase();
    if(stepsOutput) {
        *stepsOutput << "Auxiliar: " << auxiliarSteps++ << endl;
        *stepsOutput << "Base: " << auxiliarBase << endl;
        *stepsOutput << auxiliar << endl;
    }

    auxiliar = auxiliar.makeBaseUsable(auxiliarBase);
    Coordinate enter = auxiliar.getCoordinateToEnterBase(auxiliarBase);
    if(stepsOutput) {
        *stepsOutput << "Auxiliar: " << auxiliarSteps++ << endl;
        *stepsOutput << "Base: " << auxiliarBase << endl;
        *stepsOutput << "Enter: (" << enter << ")" << endl;
        *stepsOutput << auxiliar << endl;
    }

    while (!enter.isNull())
    {
        int leaveIdx = auxiliarBase.findIndexByX(enter.x);
        auxiliarBase[leaveIdx] = enter;
        auxiliar = auxiliar.makeBaseUsable(auxiliarBase);
        enter = auxiliar.getCoordinateToEnterBase(auxiliarBase);
        if(stepsOutput) {
            *stepsOutput << "Auxiliar: " << auxiliarSteps++ << endl;
            *stepsOutput << "Base: " << auxiliarBase << endl;
            *stepsOutput << "Enter: (" << enter << ")" << endl;
            *stepsOutput << auxiliar << endl;
        }
    }
    if (auxiliar.v.isNegative())
    {
        resultOutput << "inviavel" << endl;
        resultOutput << auxiliar.certificate << endl;
    }
    else
    {
        Base base;
        int steps = 0;
        Tabloid tabloid = firstTabloid.continueUsingAuxiliar(auxiliar, auxiliarBase, base);
        if(stepsOutput) {
            *stepsOutput << "Step: " << steps++ << endl;
            *stepsOutput << "Base: " << base << endl;
            *stepsOutput << tabloid << endl;
        }
        tabloid = tabloid.makeBaseUsable(base);
        enter = tabloid.getCoordinateToEnterBase(base);
        if(stepsOutput) {
            *stepsOutput << "Step: " << steps++ << endl;
            *stepsOutput << "Base: " << base << endl;
            *stepsOutput << "Enter: " << enter << endl;
            *stepsOutput << tabloid << endl;
        }
        while (!enter.isNull())
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
            resultOutput << "ilimitada" << endl;
        }
        else
        {
            resultOutput << "otima" << endl;
            resultOutput << tabloid.v << endl;
        }
        resultOutput << result << endl;
        if (otima)
        {
            resultOutput << tabloid.certificate << endl;
        }
        else
        {
            for (int i = 0; i < tabloid.C.size(); i++)
            {
                if (i)
                    resultOutput << " ";
                if (tabloid.C[i].isNegative())
                {
                    resultOutput << Fraction(1);
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
                    if (!coord.isNull())
                    {
                        resultOutput << -tabloid.A[coord.x][negativeColumn];
                    }
                    else
                    {
                        resultOutput << Fraction(0);
                    }
                }
            }
            resultOutput << endl;
        }
    }
}