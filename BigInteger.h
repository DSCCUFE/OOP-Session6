#pragma once
#include <iostream>
using namespace std;
class BigInteger
{
	int *data = nullptr;
	int digits;
	bool sign = true; // +ve ->true, -ve false

public:
	BigInteger();
	BigInteger(long long number);
	BigInteger(const BigInteger &obj);
	BigInteger(string number);
	void setDigits(long long number);
	BigInteger operator+(BigInteger &obj);
	BigInteger operator+(long long number);
	BigInteger operator-(long long number);
	BigInteger operator*(BigInteger &obj);
	BigInteger operator*(long long number);
	BigInteger operator+=(BigInteger &obj);
	BigInteger operator+=(long long number);
	BigInteger operator-=(BigInteger &obj);
	BigInteger operator-=(long long number);
	BigInteger operator*=(BigInteger &obj);
	BigInteger operator*=(long long number);
	bool operator>(BigInteger &obj);
	bool operator==(BigInteger &obj);
	bool operator<(BigInteger &obj);
	bool operator<=(BigInteger &obj);
	bool operator>=(BigInteger &obj);
	bool operator!=(BigInteger &obj);
	BigInteger operator-();
	BigInteger operator++(int);
	BigInteger operator++();
	int &operator[](int index);
	BigInteger operator^(BigInteger &obj);
	friend ostream &operator<<(ostream &output, BigInteger &obj);

	//I forgot to add those in the session:
	BigInteger operator=(const BigInteger &obj);//so important
	BigInteger operator-(BigInteger &obj);
	BigInteger operator--(int);
	BigInteger operator--();
	~BigInteger();//so important
};
