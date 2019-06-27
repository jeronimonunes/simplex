#ifndef STRING_UTIL_HH
#define STRING_UTIL_HH
#include <string>
#include <vector>
#include "bigint/BigInteger.hh"

using namespace std;

const vector<string> explode(const string& s, const char& c, const char c2 = '\0');

#endif