#include "BigInteger.h"
BigInteger::BigInteger()
{
	digits = 0;
}
BigInteger::BigInteger(long long number)
{
	if (number < 0)
		sign = false;
	else
		sign = true;
	this->digits = 100;
	data = new int[this->digits];
	for (int i = 0; i < this->digits; i++)
	{
		data[i] = 0;
	}
	int index = 0;
	while (number != 0)
	{
		data[index] = number % 10;
		number /= 10;
		index++;
	}
}
BigInteger::BigInteger(const BigInteger &obj)
{
	sign = obj.sign;
	data = new int[obj.digits];
	this->digits = obj.digits;
	for (int i = 0; i < obj.digits; i++)
	{
		data[i] = obj.data[i];
	}
}
BigInteger::BigInteger(string number)
{
	if (number[0] == '-')
	{
		data = new int[number.size() - 1];
		sign = false;
		digits = number.size() - 1;
	}
	else
	{
		data = new int[number.size()];
		sign = true;
		digits = number.size();
	}
	int index = digits - 1;
	for (int i = 0; i < number.size(); i++)
	{
		int num = number[i] - '0';
		if (num >= 0 && num <= 9)
			data[index] = num;
		index--;
	}
}
void BigInteger::setDigits(long long number)
{ //used after default constructor
	digits = number;
	if (data)
		delete[] data;
	data = new int[this->digits];
	for (int i = 0; i < this->digits; i++)
	{
		data[i] = 0;
	}
}
int &BigInteger::operator[](int index)
{
	return data[index];
}
BigInteger BigInteger::operator+(BigInteger &obj)
{
	BigInteger result;
	result.setDigits(max(obj.digits, digits) + 1);
	for (int i = 0; i < result.digits; i++)
	{
		if (i >= obj.digits && i < digits)
		{
			result[i] = data[i];
		}
		else if (i >= digits && i < obj.digits)
		{
			result[i] = obj.data[i];
		}
		else if (i >= digits && i >= obj.digits)
		{
			result[i] = 0;
		}
		else
		{
			result[i] = data[i] + obj.data[i];
		}
	}
	for (int i = 0; i < result.digits - 1; i++)
	{
		int currentValue = result[i] % 10;
		int carry = result[i] / 10;
		result[i] = currentValue;
		result[i + 1] += carry;
	}
	return result;
}
BigInteger BigInteger::operator+(long long number)
{
	BigInteger result(number);
	return result + *this;
}
BigInteger BigInteger::operator*(BigInteger &obj)
{
	BigInteger result;
	if (!sign && !obj.sign)
		result.sign = true;
	if (sign && !obj.sign)
		result.sign = false;
	if (!sign && obj.sign)
		result.sign = false;
	if (sign && obj.sign)
		result.sign = true;
	result.setDigits(digits + obj.digits);
	for (int i = 0; i < digits; i++)
	{
		for (int j = 0; j < obj.digits; j++)
		{
			result[i + j] += data[i] * obj[j];
		}
	}
	for (int i = 0; i < result.digits - 1; i++)
	{
		int currentValue = result[i] % 10;
		int carry = result[i] / 10;
		result[i] = currentValue;
		result[i + 1] += carry;
	}
	return result;
}
BigInteger BigInteger::operator*(long long number)
{
	BigInteger result(number);
	return result * (*this);
}
BigInteger BigInteger::operator+=(BigInteger &obj)
{
	*this = *this + obj;
	return *this;
}
BigInteger BigInteger::operator+=(long long number)
{
	*this = *this + number;
	return *this;
}
BigInteger BigInteger::operator*=(BigInteger &obj)
{
	*this = *this * obj;
	return *this;
}
BigInteger BigInteger::operator*=(long long number)
{
	*this = *this * number;
	return *this;
}
bool BigInteger::operator==(BigInteger &obj)
{
	if (sign && !obj.sign || !sign && obj.sign)
		return false;
	int trueSize1 = digits - 1;
	int trueSize2 = obj.digits - 1;

	while (data[trueSize1] == 0 && trueSize1 >= 0)
		trueSize1--;
	while (obj[trueSize2] == 0 && trueSize2 >= 0)
		trueSize2--;
	if (trueSize1 != trueSize2)
		return false;
	for (int i = 0; i <= trueSize1; i++)
	{
		if (data[i] != obj[i])
			return false;
	}
	return true;
}
bool BigInteger::operator<(BigInteger &obj)
{
	return !(*this > obj) && !(*this == obj);
}
bool BigInteger::operator<=(BigInteger &obj)
{
	return !(*this > obj);
}
bool BigInteger::operator>=(BigInteger &obj)
{
	return (*this > obj) || (*this == obj);
}
bool BigInteger::operator!=(BigInteger &obj)
{
	return !(*this == obj);
}
BigInteger BigInteger::operator-()
{
	this->sign = !(this->sign);
	return *this;
}
BigInteger BigInteger::operator++(int)
{
	BigInteger temp = *this;
	*this += 1;
	return temp;
} //postfix
BigInteger BigInteger::operator++()
{
	*this += 1;
	return *this;
} //prefix

bool BigInteger::operator>(BigInteger &obj)
{
	if (sign && !obj.sign)
	{
		return true;
	}
	if (!sign && obj.sign)
	{
		return false;
	}
	int trueSize1 = digits - 1;
	int trueSize2 = obj.digits - 1;

	while (data[trueSize1] == 0 && trueSize1 >= 0)
		trueSize1--;
	while (obj[trueSize2] == 0 && trueSize2 >= 0)
		trueSize2--;
	if (trueSize1 < trueSize2)
	{
		return !sign;
	}
	else if (trueSize1 > trueSize2)
	{
		return sign;
	}
	//same size and same sign

	bool greater;
	int i;
	for (i = digits - 1; i >= 0; i--)
	{
		if (data[i] > obj.data[i])
		{
			return sign;
		}
		if (data[i] < obj.data[i])
		{
			return !sign;
		}
	}
	return false; //equal
}
BigInteger BigInteger::operator^(BigInteger &power)
{
	BigInteger result;
	result.setDigits(1000);
	result += 1;
	for (BigInteger i = 0; i < power; i++)
	{
		result *= (*this);
	}
	return result;
}

//I forgot to add those in the session:
BigInteger BigInteger::operator=(const BigInteger &obj) //very important when you have aggregation
{
	sign = obj.sign;
	if (data != nullptr)
	{
		delete[] data;
	}
	data = new int[obj.digits];
	for (int i = 0; i < obj.digits; i++)
	{
		data[i] = obj.data[i];
	}
	this->digits = obj.digits;
	return *this;
}
BigInteger BigInteger::operator-(BigInteger &obj)
{
	if (*this == obj)
		return BigInteger(0);
	BigInteger result;
	BigInteger *bigger;
	BigInteger *smaller;
	if (*this < obj)
	{
		result.sign = false;
		bigger = &obj;
		smaller = this;
	}
	else
	{
		result.sign = true;
		bigger = this;
		smaller = &obj;
	}

	result.setDigits(bigger->digits);
	//calculate each digit
	for (int i = 0; i < bigger->digits; i++)
	{
		if (i < obj.digits)
			result[i] = bigger->data[i] - smaller->data[i];
		else
			result[i] = bigger->data[i];
	}
	for (int i = 0; i < bigger->digits; i++)
	{

		if (result[i] < 0)
		{
			result[i] += 10;
			if (i + 1 < bigger->digits)
				result.data[i + 1]--;
		}
	}
	return result;
}

BigInteger BigInteger::operator-(long long number)
{
	BigInteger num(number);
	return *this - num;
}

BigInteger BigInteger::operator-=(BigInteger &obj)
{
	*this = *this - obj;
	return *this;
}
BigInteger BigInteger::operator-=(long long number)
{
	BigInteger temp(number);
	*this -= temp;
	return *this;
}
BigInteger BigInteger::operator--(int)
{
	BigInteger temp = *this;
	*this -= 1;
	return temp;
} //postfix
BigInteger BigInteger::operator--()
{
	*this -= 1;
	return *this;
} //prefix

// I added this from the main file
ostream& operator<<(ostream& output, BigInteger& obj) {
	int cnt = obj.digits - 1;
	while (obj.data[cnt] == 0 && cnt >= 0) {
		cnt--;
	}
	if (cnt == -1) {

		output << 0;
		return output;
	}
	if (obj.sign == false) {
		cout << '-';
	}
	for (int i = cnt; i >= 0; i--)
	{
		cout << obj.data[i];
	}
	return output;
}

BigInteger::~BigInteger() {
	delete[] data;
}