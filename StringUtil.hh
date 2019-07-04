#ifndef STRING_UTIL_HH
#define STRING_UTIL_HH
#include <string>
#include <vector>
#include "bigint/BigInteger.hh"

using namespace std;

const vector<string> explode(const string &s, std::initializer_list<char> list);

#endif