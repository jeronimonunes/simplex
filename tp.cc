#include "./src/Simplex.hh"

using namespace std;

int main()
{
    unsigned int n; // number of restrictions
    unsigned int m; // number of variables
    cin >> n >> m;

    Vector C;
    for (unsigned int i = 0; i < m; i++)
    {
        int val;
        cin >> val;
        C.push_back(-val);
    }
    for (unsigned int i = 0; i < n; i++)
    {
        C.push_back(0);
    }

    Matrix A;
    Vector B;
    for (unsigned int j = 0; j < n; j++)
    {
        Vector line;
        for (unsigned int i = 0; i < m; i++)
        {
            int val;
            cin >> val;
            line.push_back(val);
        }
        for (unsigned int i = 0; i < n; i++)
        {
            line.push_back(i == j);
        }
        int b;
        cin >> b;
        B.push_back(b);
        A.push_back(line);
    }

    Tabloid tabloid(A, B, C, 0);

    Result result = runSimplex(tabloid);

    switch (result.type)
    {
    case ResultType::ILIMITED:
        cout << "ilimitada" << endl;
        cout << result.solution.crop(m) << endl;
        cout << result.certificate.crop(m) << endl;
        break;
    case ResultType::UNFEASIBLE:
        cout << "inviavel" << endl;
        cout << result.certificate.crop(n) << endl;
        break;
    case ResultType::LIMITED:
        cout << "otima" << endl;
        cout << result.value << endl;
        cout << result.solution.crop(m) << endl;
        cout << result.certificate.crop(n) << endl;
        break;
    }
    return 0;
}
