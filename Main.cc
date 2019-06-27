#include "Vector.hh"
#include "Matrix.hh"
#include "StringUtil.hh"
#include "Simplex.hh"
#include <iostream>

using namespace std;

int main()
{
    //Processing input
    Matrix A;
    Vector B;
    Vector C;
    Vector certificate;
    Matrix certificateMatrix;
    Fraction v;

    string line;
    //tabloid header
    if (!getline(cin, line))
    {
        cerr << "Invalid input" << endl;
        return -1;
    }

    vector<string> pieces = explode(line, '|');
    if (pieces.size() != 3)
    {
        cerr << "Invalid input" << endl;
        return -1;
    }

    vector<string> values = explode(pieces[0], ' ', '\t');
    for (int i = 0; i < values.size(); i++)
    {
        certificate.push_back(Fraction::fromString(values[i]));
    }

    values = explode(pieces[1], ' ', '\t');

    for (int i = 0; i < values.size(); i++)
    {
        C.push_back(Fraction::fromString(values[i]));
    }

    v = Fraction::fromString(values[2]);

    //ignored line
    if (!getline(cin, line))
    {
        cerr << "Invalid input" << endl;
        return -1;
    }

    //tabloid body
    for (int i = 0; i < certificate.size(); i++)
    {
        if (!getline(cin, line))
        {
            cerr << "Invalid input" << endl;
            return -1;
        }
        vector<string> pieces = explode(line, '|');
        if (pieces.size() != 3)
        {
            cerr << "Invalid input" << endl;
            return -1;
        }

        values = explode(pieces[0], ' ', '\t');
        Vector certificateLine;
        for (int j = 0; j < values.size(); j++)
        {
            certificateLine.push_back(Fraction::fromString(values[j]));
        }
        certificateMatrix.push_back(certificateLine);

        values = explode(pieces[1], ' ', '\t');
        Vector restrictionLine;
        for (int j = 0; j < values.size(); j++)
        {
            restrictionLine.push_back(Fraction::fromString(values[j]));
        }
        A.push_back(restrictionLine);

        B.push_back(Fraction::fromString(values[2]));
    }

    runSimplex(certificate, certificateMatrix, A, B, C, v);

    return 0;
}
