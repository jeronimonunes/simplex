#include "Io.hh"
#include "Simplex.hh"

using namespace std;

int main()
{
    //Processing input
    Tabloid tabloid = readString(cin);

    runSimplex(tabloid, cout);

    return 0;
}