#include "Simplex.hh"

Result runSimplex(Tabloid &firstTabloid)
{
  firstTabloid = firstTabloid.fixNegativeB();

  Tabloid auxiliar = firstTabloid.makeAuxiliarSimplex();

  bool run = true;

  while (run)
  {
    auxiliar = auxiliar.makeBaseUsable();
    auxiliar = auxiliar.runSimplexStep(run);
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
    Tabloid tabloid = firstTabloid.continueUsingAuxiliar(auxiliar);

    bool run = true;
    while (run)
    {
      tabloid = tabloid.makeBaseUsable();
      tabloid = tabloid.runSimplexStep(run);
    }
    Vector result;
    for (unsigned int y = 0; y < tabloid.C.size(); y++)
    {
      Fraction v = tabloid.C[y];
      if (v.isZero())
      {
        bool found = false;
        for (unsigned int p = 0; p < tabloid.base.size(); p++)
        {
          if (tabloid.base[p].y == (int)y)
          {
            found = true;
            result.push_back(tabloid.B[tabloid.base[p].x]);
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
          for (unsigned int p = 0; p < tabloid.base.size(); p++)
          {
            if (tabloid.base[p].y == (int)i)
            {
              coord = tabloid.base[p];
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