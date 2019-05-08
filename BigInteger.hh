#include <string>
#define MAX 10000 // for strings

using namespace std;
//-------------------------------------------------------------
class BigInteger
{
private:
	string number;
	bool sign;
	

public:
	BigInteger();					// empty constructor initializes zero
	BigInteger(string s);			// "string" constructor
	BigInteger(string s, bool sin); // "string" constructor
	BigInteger(int n);				// "int" constructor
	void setNumber(string s);
	const string &getNumber(); // retrieves the number
	void setSign(bool s);
	const bool &getSign();
	BigInteger absolute(); // returns the absolute value
	void operator=(BigInteger b);
	bool operator==(BigInteger b);
	bool operator!=(BigInteger b);
	bool operator>(BigInteger b);
	bool operator<(BigInteger b);
	bool operator>=(BigInteger b);
	bool operator<=(BigInteger b);
	BigInteger &operator++();   // prefix
	BigInteger operator++(int); // postfix
	BigInteger &operator--();   // prefix
	BigInteger operator--(int); // postfix
	BigInteger operator+(BigInteger b);
	BigInteger operator-(BigInteger b);
	BigInteger operator*(BigInteger b);
	BigInteger operator/(BigInteger b);
	BigInteger operator%(BigInteger b);
	BigInteger &operator+=(BigInteger b);
	BigInteger &operator-=(BigInteger b);
	BigInteger &operator*=(BigInteger b);
	BigInteger &operator/=(BigInteger b);
	BigInteger &operator%=(BigInteger b);
	BigInteger &operator[](int n);
	BigInteger operator-(); // unary minus sign
	operator string();		// for conversion from BigInteger to string
	double eval();
private:
	string workPiece(string & dividendos, string piece, int idx, string &divisors, BigInteger &divisor, string& res);
	pair<BigInteger, BigInteger> meudivide(BigInteger a, BigInteger b);
	bool equals(BigInteger n1, BigInteger n2);
	bool less(BigInteger n1, BigInteger n2);
	bool greater(BigInteger n1, BigInteger n2);
	string add(string number1, string number2);
	string subtract(string number1, string number2);
	string multiply(string n1, string n2);
	string toString(long long n);
	string toString(int n);
	long long toInt(string s);
};
