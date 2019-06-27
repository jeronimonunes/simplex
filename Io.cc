#include "Io.hh"
#include "StringUtil.hh"

Tabloid readString(std::istream &istream)
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

    vector<string> pieces = explode(line, '|');
    if (pieces.size() != 3)
    {
        throw "Invalid input";
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
    if (!getline(istream, line))
    {
        throw "Invalid input";
    }

    //tabloid body
    for (int i = 0; i < certificate.size(); i++)
    {
        if (!getline(istream, line))
        {
            throw "Invalid input";
        }
        vector<string> pieces = explode(line, '|');
        if (pieces.size() != 3)
        {
            throw "Invalid input";
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
    return Tabloid(certificate, certificateMatrix, A, B, C, v);
}