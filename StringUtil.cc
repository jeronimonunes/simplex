#include "StringUtil.hh"

using namespace std;

const vector<string> explode(const string& s, const char& c, const char c2)
{
	string buff{""};
	vector<string> v;
	
	for(char n:s)
	{
		if(n != c && n != c2) buff+=n; else
		if((n == c || n == c2) && buff != "") { v.push_back(buff); buff = ""; }
	}
	if(buff != "") v.push_back(buff);
	
	return v;
}