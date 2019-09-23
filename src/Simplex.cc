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
        auto itr = tabloid.base.yfind(y);
        if (itr == tabloid.base.yend())
        {
          result.push_back(0);
        }
        else
        {
          auto const &[y, x] = *itr;
          result.push_back(tabloid.B[x]);
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
          auto itr = tabloid.base.yfind(i);
          if (itr == tabloid.base.yend())
          {
            cert[i] = 0;
          }
          else
          {
            const auto &[y, x] = *itr;
            cert[i] = -tabloid.A[x][negativeColumn];
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
