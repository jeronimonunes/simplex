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
        ResultType::INFEASIBLE,
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
    return tabloid.getResult();
  }
}
