#include "Io.hh"
#include "Simplex.hh"

using namespace std;

int main()
{
    try {
    //Processing input
    Tabloid tabloid = readString(cin);

    Result result = runSimplex(tabloid);

    switch (result.type)
    {
    case ResultType::ILIMITED:
        cout << "ilimitada" << endl;
        cout << result.solution << endl;
        cout << result.certificate << endl;
        break;
    case ResultType::UNFEASIBLE:
        cout << "inviavel" << endl;
        cout << result.certificate << endl;
        break;
    case ResultType::LIMITED:
        cout << "otima" << endl;
        cout << result.value << endl;
        cout << result.solution << endl;
        cout << result.certificate << endl;
        break;
    }
    } catch (char const* s) {
        cerr << s << endl;
    }

    return 0;
}
