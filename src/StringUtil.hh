#ifndef STRING_UTIL_HH
#define STRING_UTIL_HH
#include <string>
#include <vector>


std::vector<std::string> explode(const std::string &s, const std::initializer_list<char>& list);

#endif