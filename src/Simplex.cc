#include "Simplex.hh"

Result runSimplex(Tabloid &firstTabloid)
{
    firstTabloid.fixNegativeB();

    Tabloid auxiliar = firstTabloid.makeAuxiliarSimplex();

    Base auxiliarBase = auxiliar.findBase();

    auxiliar = auxiliar.makeBaseUsable(auxiliarBase);
    Coordinate enter = auxiliar.getCoordinateToEnterBase(auxiliarBase);

    while (!enter.isNull())
    {
        int leaveIdx = auxiliarBase.findIndexByX(enter.x);
        auxiliarBase[leaveIdx] = enter;
        auxiliar = auxiliar.makeBaseUsable(auxiliarBase);
        enter = auxiliar.getCoordinateToEnterBase(auxiliarBase);
    }

    if (auxiliar.v.isNegative())
    {
        return {
            ResultType::UNFEASIBLE,
            auxiliar.certificate,
            0,
            Vector(0)};
    }
    else
    {
        Base base;
        Tabloid tabloid = firstTabloid.continueUsingAuxiliar(auxiliar, auxiliarBase, base);
        tabloid = tabloid.makeBaseUsable(base);
        enter = tabloid.getCoordinateToEnterBase(base);
        while (!enter.isNull())
        {
            int leaveIdx = base.findIndexByX(enter.x);
            base[leaveIdx] = enter;
            tabloid = tabloid.makeBaseUsable(base);
            enter = tabloid.getCoordinateToEnterBase(base);
        }
        Vector result;
        for (unsigned int y = 0; y < tabloid.C.size(); y++)
        {
            Fraction v = tabloid.C[y];
            if (v.isZero())
            {
                bool found = false;
                for (unsigned int p = 0; p < base.size(); p++)
                {
                    if (base[p].y == (int)y)
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
        for (unsigned int g = 0; g < tabloid.C.size(); g++)
        {
            if (tabloid.C[g].isNegative())
            {
                otima = false;
                negativeColumn = g;
                break;
            }
        }
        if (otima)
        {
            return {
                ResultType::LIMITED,
                tabloid.certificate,
                tabloid.v,
                result};
        }
        else
        {
            Vector cert(tabloid.C.size());
            for (unsigned int i = 0; i < tabloid.C.size(); i++)
            {
                if (tabloid.C[i].isNegative())
                {
                    cert[i] = 1;
                }
                else
                {
                    Coordinate coord = NULL_COORDINATE;
                    for (unsigned int p = 0; p < base.size(); p++)
                    {
                        if (base[p].y == (int)i)
                        {
                            coord = base[p];
                        }
                    }
                    if (!coord.isNull())
                    {
                        cert[i] = -tabloid.A[coord.x][negativeColumn];
                    }
                    else
                    {
                        cert[i] = 0;
                    }
                }
            }
            return {
                ResultType::ILIMITED,
                cert,
                0,
                result};
        }
    }
}