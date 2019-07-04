#include "StringUtil.hh"
#include <algorithm>

using namespace std;

const vector<string> explode(const string &s, std::initializer_list<char> list)
{
	string buff{""};
	vector<string> v;

	for (char n : s)
	{
		bool found = std::find(list.begin(), list.end(), n) != list.end();
		if (!found)
			buff += n;
		else if (found && buff != "")
		{
			v.push_back(buff);
			buff = "";
		}
	}
	if (buff != "")
		v.push_back(buff);

	return v;
}