#ifndef SIMPLEX_HH
#define SIMPLEX_HH
#include "Tabloid.hh"

enum class ResultType {
    UNFEASIBLE,
    ILIMITED,
    LIMITED
};

class Result {
    public:
    ResultType type;
    Vector certificate;
    Fraction value;
    Vector solution;
};

Result runSimplex(Tabloid &tabloid);

#endif