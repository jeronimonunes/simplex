#include "Io.hh"
#include "StringUtil.hh"

using namespace std;

const initializer_list<char> SPACES = {' ', '\t', '\r', '\n'};

Tabloid readString(istream &istream)
{
    Matrix A;
    Vector B;
    Vector C;
    Vector certificate;
    Matrix certificateMatrix;
    Fraction v;

    string line;
    //tabloid header
    if (!getline(istream, line))
    {
        throw "Invalid input";
    }

    vector<string> pieces = explode(line, {'|'});
    if (pieces.size() != 3)
    {
        throw "Invalid input";
    }

    vector<string> values = explode(pieces[0], SPACES);
    for (unsigned int i = 0; i < values.size(); i++)
    {
        certificate.push_back(Fraction::fromString(values[i]));
    }

    values = explode(pieces[1], SPACES);

    for (unsigned int i = 0; i < values.size(); i++)
    {
        C.push_back(Fraction::fromString(values[i]));
    }

    values = explode(pieces[2], SPACES);

    if (values.size() != 1)
    {
        throw "Invalid input";
    }

    v = Fraction::fromString(values[0]);

    //ignored line
    if (!getline(istream, line))
    {
        throw "Invalid input";
    }

    //tabloid body
    for (unsigned int i = 0; i < certificate.size(); i++)
    {
        if (!getline(istream, line))
        {
            throw "Invalid input";
        }
        vector<string> pieces = explode(line, {'|'});
        if (pieces.size() != 3)
        {
            throw "Invalid input";
        }

        values = explode(pieces[0], SPACES);
        Vector certificateLine;
        for (unsigned int j = 0; j < values.size(); j++)
        {
            certificateLine.push_back(Fraction::fromString(values[j]));
        }
        certificateMatrix.push_back(certificateLine);

        values = explode(pieces[1], SPACES);
        Vector restrictionLine;
        for (unsigned int j = 0; j < values.size(); j++)
        {
            restrictionLine.push_back(Fraction::fromString(values[j]));
        }
        A.push_back(restrictionLine);

        values = explode(pieces[2], SPACES);

        if (values.size() != 1)
        {
            throw "Invalid input";
        }

        B.push_back(Fraction::fromString(values[0]));
    }
    Tabloid t = Tabloid(certificate, certificateMatrix, A, B, C, v, Base());
    return t;
}