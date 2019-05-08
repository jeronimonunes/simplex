#ifndef BIGINTEGER_H
#define BIGINTEGER_H

#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include "BigInteger.hh"
#include <limits>

BigInteger MAX(BigInteger::toString(std::numeric_limits<long long>::max()));

BigInteger::BigInteger() // empty constructor initializes zero
{
	native = true;
	value = 0;
}
//-------------------------------------------------------------
BigInteger::BigInteger(string s) // "string" constructor
{
	native = false;
	if (s.length() == 0)
	{
		native = true;
		value = 0;
	}
	else if (isdigit(s[0])) // if not signed
	{
		number = s;
		sign = false; // +ve
	}
	else
	{
		number = s.substr(1);
		sign = (s[0] == '-');
	}
}
//-------------------------------------------------------------
BigInteger::BigInteger(string s, bool sin) // "string" constructor
{
	native = false;
	number = s;
	sign = sin;
}
//-------------------------------------------------------------
BigInteger::BigInteger(long long n) // "long long" constructor
{
	native = true;
	value = n;
}
//-------------------------------------------------------------
void BigInteger::setNumber(string s)
{
	number = s;
}
//-------------------------------------------------------------
const string &BigInteger::getNumber() // retrieves the number
{
	return number;
}
//-------------------------------------------------------------
void BigInteger::setSign(bool s)
{
	sign = s;
}
//-------------------------------------------------------------
const bool &BigInteger::getSign()
{
	return sign;
}
//-------------------------------------------------------------
// returns the absolute value
BigInteger BigInteger::absolute()
{
	if (native)
	{
		if (value < 0)
		{
			return BigInteger(-value);
		}
		else
		{
			return *this;
		}
	}
	else
	{
		if (sign)
		{
			return BigInteger(number); // +ve by default
		}
		else
		{
			return *this;
		}
	}
}
//-------------------------------------------------------------
void BigInteger::operator=(BigInteger b)
{
	number = b.number;
	native = b.native;
	value = b.value;
	sign = b.sign;
}
//-------------------------------------------------------------
bool BigInteger::operator==(BigInteger b)
{
	if (native && b.native)
	{
		return value == b.value;
	}
	else if (native)
	{
		return false;
	}
	else if (b.native)
	{
		return false;
	}
	else
	{
		return equals((*this), b);
	}
}
//-------------------------------------------------------------
bool BigInteger::operator!=(BigInteger b)
{
	if (native && b.native)
	{
		return value != b.value;
	}
	else if (native)
	{
		return true;
	}
	else if (b.native)
	{
		return true;
	}
	else
	{
		return sign != b.sign || number != b.number;
	}
}
//-------------------------------------------------------------
bool BigInteger::operator>(BigInteger b)
{
	if (native && b.native)
	{
		return value > b.value;
	}
	else if (native)
	{
		return false;
	}
	else if (b.native)
	{
		return true;
	}
	else
	{
		return greater((*this), b);
	}
}
//-------------------------------------------------------------
bool BigInteger::operator<(BigInteger b)
{
	if (native && b.native)
	{
		return value < b.value;
	}
	else if (native)
	{
		return true;
	}
	else if (b.native)
	{
		return false;
	}
	else
	{
		return less((*this), b);
	}
}
//-------------------------------------------------------------
bool BigInteger::operator>=(BigInteger b)
{
	if (native && b.native)
	{
		return value >= b.value;
	}
	else if (native || b.native)
	{
		return false;
	}
	else
	{
		return greater((*this), b) || equals((*this), b);
	}
}
//-------------------------------------------------------------
bool BigInteger::operator<=(BigInteger b)
{
	if (native && b.native)
	{
		return value <= b.value;
	}
	else if (native || b.native)
	{
		return false;
	}
	else
	{
		return less((*this), b) || equals((*this), b);
	}
}
//-------------------------------------------------------------
// increments the value, then returns its value
BigInteger &BigInteger::operator++() // prefix
{
	(*this) = (*this) + 1;
	return (*this);
}
//-------------------------------------------------------------
// returns the value, then increments its value
BigInteger BigInteger::operator++(int) // postfix
{
	BigInteger before = (*this);

	(*this) = (*this) + 1;

	return before;
}
//-------------------------------------------------------------
// decrements the value, then return it
BigInteger &BigInteger::operator--() // prefix
{
	(*this) = (*this) - 1;
	return (*this);
}
//-------------------------------------------------------------
// return the value, then decrements it
BigInteger BigInteger::operator--(int) // postfix
{
	BigInteger before = (*this);

	(*this) = (*this) - 1;

	return before;
}
//-------------------------------------------------------------
BigInteger BigInteger::operator+(BigInteger b)
{
	if (native && b.native)
	{
		if (value <= std::numeric_limits<long long>::max() - b.value)
		{
			return value + b.value;
		}
	}
	if (native)
	{
		string s = toString(value);
		if (isdigit(s[0]))
		{
			sign = false;
			number = s;
		}
		else
		{
			sign = true;
			number = s.substr(1);
		}
	}
	if (b.native)
	{
		string s = toString(b.value);
		if (isdigit(s[0]))
		{
			b.sign = false;
			b.number = s;
		}
		else
		{
			b.sign = true;
			b.number = s.substr(1);
		}
	}
	BigInteger addition;
	addition.native = false;
	if (sign == b.sign) // both +ve or -ve
	{
		addition.number = add(number, b.number);
		addition.sign = sign;
	}
	else // sign different
	{
		if (absolute() > b.absolute())
		{
			addition.number = subtract(number, b.number);
			addition.sign = sign;
		}
		else
		{
			addition.number = subtract(b.number, number);
			addition.sign = b.sign;
		}
		if (addition < MAX)
		{
			addition.value = toInt(addition.number);
			if (addition.sign)
			{
				addition.value = -addition.value;
			}
			addition.native = true;
		}
	}
	if (addition.number == "0") // avoid (-0) problem
		addition.sign = false;

	return addition;
}
//-------------------------------------------------------------
BigInteger BigInteger::operator-(BigInteger b)
{
	b.sign = !b.sign; // x - y = x + (-y)
	return (*this) + b;
}
//-------------------------------------------------------------
BigInteger BigInteger::operator*(BigInteger b)
{
	if ((*this) == 0 || b == 0)
	{
		return 0;
	}
	else if (native && b.native)
	{
		if (value <= std::numeric_limits<long long>::max() / b.value)
		{
			return value * b.value;
		}
	}
	if (native)
	{
		string s = toString(value);
		if (isdigit(s[0]))
		{
			sign = false;
			number = s;
		}
		else
		{
			sign = true;
			number = s.substr(1);
		}
	}
	if (b.native)
	{
		string s = toString(b.value);
		if (isdigit(s[0]))
		{
			b.sign = false;
			b.number = s;
		}
		else
		{
			b.sign = true;
			b.number = s.substr(1);
		}
	}
	BigInteger mul;

	mul.number = multiply(number, b.number);
	mul.sign = sign != b.sign;
	mul.native = false;

	if (mul.number == "0") // avoid (-0) problem
		mul.sign = false;

	return mul;
}
//-------------------------------------------------------------
BigInteger BigInteger::operator/(BigInteger b)
{
	if (b == 1)
	{
		return *this;
	}
	else if (native && b.native)
	{
		return value / b.value;
	}
	else if (native)
	{
		string s = toString(value);
		if (isdigit(s[0]))
		{
			sign = false;
			number = s;
		}
		else
		{
			sign = true;
			number = s.substr(1);
		}
	}
	else if (b.native)
	{
		string s = toString(b.value);
		if (isdigit(s[0]))
		{
			b.sign = false;
			b.number = s;
		}
		else
		{
			b.sign = true;
			b.number = s.substr(1);
		}
	}
	BigInteger divide = meudivide((*this), b).first;
	if (divide < MAX)
	{
		divide.value = toInt(divide.number);
		if (divide.sign)
		{
			divide.value = -divide.value;
		}
		divide.native = true;
	}
	return divide;
}
//-------------------------------------------------------------
BigInteger BigInteger::operator%(BigInteger b)
{
	if (b == 1)
	{
		return 0;
	}
	else if (native && b.native)
	{
		return value % b.value;
	}
	else if (native)
	{
		string s = toString(value);
		if (isdigit(s[0]))
		{
			sign = false;
			number = s;
		}
		else
		{
			sign = true;
			number = s.substr(1);
		}
	}
	else if (b.native)
	{
		string s = toString(b.value);
		if (isdigit(s[0]))
		{
			b.sign = false;
			b.number = s;
		}
		else
		{
			b.sign = true;
			b.number = s.substr(1);
		}
	}
	BigInteger mod = meudivide((*this), b).second;
	if (mod < MAX)
	{
		mod.value = toInt(mod.number);
		if (mod.sign)
		{
			mod.value = -mod.value;
		}
		mod.native = true;
	}
	return mod;
}
//-------------------------------------------------------------
BigInteger &BigInteger::operator+=(BigInteger b)
{
	(*this) = (*this) + b;
	return (*this);
}
//-------------------------------------------------------------
BigInteger &BigInteger::operator-=(BigInteger b)
{
	(*this) = (*this) - b;
	return (*this);
}
//-------------------------------------------------------------
BigInteger &BigInteger::operator*=(BigInteger b)
{
	(*this) = (*this) * b;
	return (*this);
}
//-------------------------------------------------------------
BigInteger &BigInteger::operator/=(BigInteger b)
{
	(*this) = (*this) / b;
	return (*this);
}
//-------------------------------------------------------------
BigInteger &BigInteger::operator%=(BigInteger b)
{
	(*this) = (*this) % b;
	return (*this);
}
//-------------------------------------------------------------
BigInteger &BigInteger::operator[](int n)
{
	return *(this + (n * sizeof(BigInteger)));
}
//-------------------------------------------------------------
BigInteger BigInteger::operator-() // unary minus sign
{
	if (native)
	{
		value = -value;
	}
	else
	{
		return BigInteger(number, !sign);
	}
}
//-------------------------------------------------------------
BigInteger::operator string() // for conversion from BigInteger to string
{
	if (native)
	{
		return toString(value);
	}
	else
	{
		string signedString = (sign) ? "-" : ""; // if +ve, don't print + sign
		signedString += number;
		return signedString;
	}
}
//-------------------------------------------------------------

bool BigInteger::equals(BigInteger n1, BigInteger n2)
{
	return n1.sign == n2.sign && n1.number == n2.number;
}

//-------------------------------------------------------------
bool BigInteger::less(BigInteger n1, BigInteger n2)
{
	bool sign1 = n1.sign;
	bool sign2 = n2.sign;

	if (sign1 && !sign2) // if n1 is -ve and n2 is +ve
		return true;

	else if (!sign1 && sign2)
		return false;

	else if (!sign1) // both +ve
	{
		if (n1.number.length() < n2.number.length())
			return true;
		if (n1.number.length() > n2.number.length())
			return false;
		return n1.number < n2.number;
	}
	else // both -ve
	{
		if (n1.number.length() > n2.number.length())
			return true;
		if (n1.number.length() < n2.number.length())
			return false;
		return n1.number > n2.number; // greater with -ve sign is LESS
	}
}
//-------------------------------------------------------------
bool BigInteger::greater(BigInteger n1, BigInteger n2)
{
	return !equals(n1, n2) && !less(n1, n2); //TODO optimize here
}

//-------------------------------------------------------------
// adds two strings and returns their sum in as a string
string BigInteger::add(string number1, string number2)
{
	string add = (number1.length() > number2.length()) ? number1 : number2;
	char carry = '0';
	int differenceInLength = abs((int)(number1.size() - number2.size()));

	if (number1.size() > number2.size())
		number2.insert(0, differenceInLength, '0'); // put zeros from left

	else // if(number1.size() < number2.size())
		number1.insert(0, differenceInLength, '0');

	for (int i = number1.size() - 1; i >= 0; --i)
	{
		add[i] = ((carry - '0') + (number1[i] - '0') + (number2[i] - '0')) + '0';

		if (i != 0)
		{
			if (add[i] > '9')
			{
				add[i] -= 10;
				carry = '1';
			}
			else
				carry = '0';
		}
	}
	if (add[0] > '9')
	{
		add[0] -= 10;
		add.insert(0, 1, '1');
	}
	return add;
}

//-------------------------------------------------------------
// subtracts two strings and returns their sum in as a string
string BigInteger::subtract(string number1, string number2)
{
	string sub = (number1.length() > number2.length()) ? number1 : number2;
	int differenceInLength = abs((int)(number1.size() - number2.size()));

	if (number1.size() > number2.size())
		number2.insert(0, differenceInLength, '0');

	else
		number1.insert(0, differenceInLength, '0');

	for (int i = number1.length() - 1; i >= 0; --i)
	{
		if (number1[i] < number2[i])
		{
			number1[i] += 10;
			number1[i - 1]--;
		}
		sub[i] = ((number1[i] - '0') - (number2[i] - '0')) + '0';
	}

	while (sub[0] == '0' && sub.length() != 1) // erase leading zeros
		sub.erase(0, 1);

	return sub;
}

//-------------------------------------------------------------
// multiplies two strings and returns their sum in as a string
string BigInteger::multiply(string n1, string n2)
{
	if (n1.length() > n2.length())
		n1.swap(n2);

	string res = "0";
	for (int i = n1.length() - 1; i >= 0; --i)
	{
		string temp = n2;
		int currentDigit = n1[i] - '0';
		int carry = 0;

		for (int j = temp.length() - 1; j >= 0; --j)
		{
			temp[j] = ((temp[j] - '0') * currentDigit) + carry;

			if (temp[j] > 9)
			{
				carry = (temp[j] / 10);
				temp[j] -= (carry * 10);
			}
			else
				carry = 0;

			temp[j] += '0'; // back to string mood
		}

		if (carry > 0)
			temp.insert(0, 1, (carry + '0'));

		temp.append((n1.length() - i - 1), '0'); // as like mult by 10, 100, 1000, 10000 and so on

		res = add(res, temp); // O(n)
	}

	while (res[0] == '0' && res.length() != 1) // erase leading zeros
		res.erase(0, 1);

	return res;
}

string digitToString(int i)
{
	switch (i)
	{
	case 0:
		return "0";
	case 1:
		return "0";
	case 2:
		return "0";
	case 3:
		return "0";
	case 4:
		return "0";
	case 5:
		return "0";
	case 6:
		return "0";
	case 7:
		return "0";
	case 8:
		return "0";
	case 9:
		return "0";
	default:
		return "";
	}
}

string BigInteger::workPiece(string &dividendos, string piece, int idx, string &divisors, BigInteger &divisor, string &res)
{
	if (piece.length() < divisors.length() || (piece.length() == divisors.length() && piece.compare(divisors) < 0))
	{
		if (idx == dividendos.length())
		{
			return piece;
		}
		piece.append(dividendos.substr(idx++, 1));
		res.append("0");
	}
	BigInteger toSub = divisor;
	BigInteger pieceI = piece;
	int i = 1;
	while (true)
	{
		toSub += divisor;
		i++;
		if (pieceI < toSub)
		{
			toSub -= divisor;
			i--;
			break;
		}
	}
	res.append(digitToString(i));
	piece = subtract(piece, toSub.number);
	if (idx < dividendos.length())
	{
		if (piece != "0")
		{
			piece.append(dividendos.substr(idx++, 1));
		}
		else
		{
			piece = dividendos.substr(idx++, 1);
		}
		return workPiece(dividendos, piece, idx, divisors, divisor, res);
	}
	else
	{
		return piece;
	}
}

pair<BigInteger, BigInteger> BigInteger::meudivide(BigInteger dividendo, BigInteger divisor)
{
	if (dividendo.sign)
	{
		pair<BigInteger, BigInteger> resp = meudivide(dividendo.absolute(), divisor.absolute());
		resp.second.setSign(true);
		if (!divisor.sign)
		{
			resp.first.setSign(true);
		}
		return resp;
	}
	else if (divisor.sign)
	{
		pair<BigInteger, BigInteger> resp = meudivide(dividendo, divisor.absolute());
		resp.first.setSign(true);
		return resp;
	}
	else if (divisor == 1)
	{
		return make_pair(dividendo, 0);
	}
	else if (divisor > dividendo)
	{
		return make_pair(0, dividendo);
	}
	else
	{
		string dividendos = dividendo.number;
		string divisors = divisor.number;
		string piece = dividendos.substr(0, divisors.length());
		string quo;
		if (BigInteger(piece) < divisor && piece.length() < dividendos.length())
		{
			piece.append(dividendos.substr(divisors.length(), 1));
		}
		string resto = workPiece(dividendos, piece, piece.length(), divisors, divisor, quo);
		return make_pair(BigInteger(quo), BigInteger(resto));
	}
}

//-------------------------------------------------------------
// converts long long to string
string BigInteger::toString(long long n)
{
	stringstream ss;
	string temp;

	ss << n;
	ss >> temp;

	return temp;
}

string BigInteger::toString(int n)
{
	stringstream ss;
	string temp;

	ss << n;
	ss >> temp;

	return temp;
}

//-------------------------------------------------------------
// converts string to long long
long long BigInteger::toInt(string s)
{
	long long sum = 0;

	for (int i = 0; i < s.length(); i++)
		sum = (sum * 10) + (s[i] - '0');

	return sum;
}

double BigInteger::eval()
{
	double val = 0;
	string s = this->number;
	for (int i = 0; i < s.length(); i++)
		val = (val * 10) + (s[i] - '0');
	if (this->sign)
	{
		val *= -1;
	}
	return val;
}

#endif