#ifndef BIGINTEGER_H
#define BIGINTEGER_H

#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include "BigInteger.hh"

BigInteger::BigInteger() // empty constructor initializes zero
{
	number = "0";
	sign = false;
}
//-------------------------------------------------------------
BigInteger::BigInteger(string s) // "string" constructor
{
	if (s.length() == 0)
	{
		setNumber("0");
		sign = false;
	}
	else if (isdigit(s[0])) // if not signed
	{
		setNumber(s);
		sign = false; // +ve
	}
	else
	{
		setNumber(s.substr(1));
		sign = (s[0] == '-');
	}
}
//-------------------------------------------------------------
BigInteger::BigInteger(string s, bool sin) // "string" constructor
{
	setNumber(s);
	setSign(sin);
}
//-------------------------------------------------------------
BigInteger::BigInteger(int n) // "int" constructor
{
	string s = toString(n);

	if (isdigit(s[0])) // if not signed
	{
		setNumber(s);
		setSign(false); // +ve
	}
	else
	{
		setNumber(s.substr(1));
		setSign(s[0] == '-');
	}
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
	return BigInteger(getNumber()); // +ve by default
}
//-------------------------------------------------------------
void BigInteger::operator=(BigInteger b)
{
	setNumber(b.getNumber());
	setSign(b.getSign());
}
//-------------------------------------------------------------
bool BigInteger::operator==(BigInteger b)
{
	return equals((*this), b);
}
//-------------------------------------------------------------
bool BigInteger::operator!=(BigInteger b)
{
	return this->getSign() != b.getSign() || this->getNumber() != b.getNumber();
}
//-------------------------------------------------------------
bool BigInteger::operator>(BigInteger b)
{
	return greater((*this), b);
}
//-------------------------------------------------------------
bool BigInteger::operator<(BigInteger b)
{
	return less((*this), b);
}
//-------------------------------------------------------------
bool BigInteger::operator>=(BigInteger b)
{
	return equals((*this), b) || greater((*this), b);
}
//-------------------------------------------------------------
bool BigInteger::operator<=(BigInteger b)
{
	return equals((*this), b) || less((*this), b);
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
	BigInteger addition;
	if (getSign() == b.getSign()) // both +ve or -ve
	{
		addition.setNumber(add(getNumber(), b.getNumber()));
		addition.setSign(getSign());
	}
	else // sign different
	{
		if (absolute() > b.absolute())
		{
			addition.setNumber(subtract(getNumber(), b.getNumber()));
			addition.setSign(getSign());
		}
		else
		{
			addition.setNumber(subtract(b.getNumber(), getNumber()));
			addition.setSign(b.getSign());
		}
	}
	if (addition.getNumber() == "0") // avoid (-0) problem
		addition.setSign(false);

	return addition;
}
//-------------------------------------------------------------
BigInteger BigInteger::operator-(BigInteger b)
{
	b.setSign(!b.getSign()); // x - y = x + (-y)
	return (*this) + b;
}
//-------------------------------------------------------------
BigInteger BigInteger::operator*(BigInteger b)
{
	BigInteger mul;

	mul.setNumber(multiply(getNumber(), b.getNumber()));
	mul.setSign(getSign() != b.getSign());

	if (mul.getNumber() == "0") // avoid (-0) problem
		mul.setSign(false);

	return mul;
}
//-------------------------------------------------------------
BigInteger BigInteger::operator/(BigInteger b)
{
	long long den = toInt(b.getNumber());
	BigInteger div;

	div.setNumber(meudivide(getNumber(), den).first);
	div.setSign(getSign() != b.getSign());

	if (div.getNumber() == "0") // avoid (-0) problem
		div.setSign(false);

	return div;
}
//-------------------------------------------------------------
BigInteger BigInteger::operator%(BigInteger b)
{
	return meudivide(*this, b).second;
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
	this->sign = !this->sign;
	return (*this);
}
//-------------------------------------------------------------
BigInteger::operator string() // for conversion from BigInteger to string
{
	string signedString = (getSign()) ? "-" : ""; // if +ve, don't print + sign
	signedString += number;
	return signedString;
}
//-------------------------------------------------------------

bool BigInteger::equals(BigInteger n1, BigInteger n2)
{
	return n1.getSign() == n2.getSign() && n1.getNumber() == n2.getNumber();
}

//-------------------------------------------------------------
bool BigInteger::less(BigInteger n1, BigInteger n2)
{
	bool sign1 = n1.getSign();
	bool sign2 = n2.getSign();

	if (sign1 && !sign2) // if n1 is -ve and n2 is +ve
		return true;

	else if (!sign1 && sign2)
		return false;

	else if (!sign1) // both +ve
	{
		if (n1.getNumber().length() < n2.getNumber().length())
			return true;
		if (n1.getNumber().length() > n2.getNumber().length())
			return false;
		return n1.getNumber() < n2.getNumber();
	}
	else // both -ve
	{
		if (n1.getNumber().length() > n2.getNumber().length())
			return true;
		if (n1.getNumber().length() < n2.getNumber().length())
			return false;
		return n1.getNumber() > n2.getNumber(); // greater with -ve sign is LESS
	}
}
//-------------------------------------------------------------
bool BigInteger::greater(BigInteger n1, BigInteger n2)
{
	return !equals(n1, n2) && !less(n1, n2);//TODO optimize here
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
	piece = subtract(piece, toSub.getNumber());
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
	if (dividendo.getSign())
	{
		pair<BigInteger, BigInteger> resp = meudivide(dividendo.absolute(), divisor.absolute());
		resp.second.setSign(true);
		if (!divisor.getSign())
		{
			resp.first.setSign(true);
		}
		return resp;
	}
	else if (divisor.getSign())
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
		string dividendos = dividendo.getNumber();
		string divisors = divisor.getNumber();
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
	string s = this->getNumber();
	for (int i = 0; i < s.length(); i++)
		val = (val * 10) + (s[i] - '0');
	if (this->getSign())
	{
		val *= -1;
	}
	return val;
}

#endif