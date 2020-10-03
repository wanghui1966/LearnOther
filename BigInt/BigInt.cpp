#include "BigInt.h"

#include <iostream>
#include <cassert>

#define CONSTRUCT_INT_SERIES(value) \
	if (value < 0) \
	{ \
		m_data = "-"; \
		value *= -1; \
	} \
	else \
	{ \
		m_data = "+"; \
	} \
	if (value == 0) \
	{ \
		m_data += "0"; \
	} \
	else \
	{ \
		std::string::size_type start = 1; \
		while (value != 0) \
		{ \
			m_data.insert(start , 1, (value % 10 + '0')); \
			value /= 10; \
		} \
	} \
	m_data_mode = "+0";

BigInt::BigInt()
{
	m_data = "+0";
	m_data_mode = "+0";
}

BigInt::BigInt(int32_t value)
{
	CONSTRUCT_INT_SERIES(value);
}

BigInt::BigInt(uint32_t value)
{
	CONSTRUCT_INT_SERIES(value);
}

BigInt::BigInt(int64_t value)
{
	CONSTRUCT_INT_SERIES(value);
}

BigInt::BigInt(uint64_t value)
{
	CONSTRUCT_INT_SERIES(value);
}

BigInt::BigInt(const std::string &value)
{
	if ((value[0] != '+') && (value[0] != '-'))
	{
		m_data = "+";
		m_data += value;
		m_data_mode = "+0";
	}
	else
	{
		m_data = value;
		m_data_mode = "+0";
	}
}

BigInt::~BigInt()
{
	m_data = "";
	m_data_mode = "";
}

BigInt::BigInt(const BigInt &value) : m_data(value.m_data), m_data_mode(value.m_data_mode)
{

}

BigInt& BigInt::operator = (const BigInt &value)
{
	m_data = value.m_data;
	m_data_mode = value.m_data_mode;
	return *this;
}

BigInt& BigInt::operator = (int32_t value)
{
	CONSTRUCT_INT_SERIES(value);
	return *this;
}

BigInt& BigInt::operator = (uint32_t value)
{
	CONSTRUCT_INT_SERIES(value);
	return *this;
}

BigInt& BigInt::operator = (int64_t value)
{
	CONSTRUCT_INT_SERIES(value);
	return *this;
}

BigInt& BigInt::operator = (uint64_t value)
{
	CONSTRUCT_INT_SERIES(value);
	return *this;
}

std::istream& operator >> (std::istream &object, BigInt &value)
{
	object >> value.m_data;
	value.AddSign();
	return object;
}

std::ostream& operator << (std::ostream &object, const BigInt &value)
{
	object << value.m_data;
	return object;
}

BigInt BigInt::operator + (const BigInt &value)
{
	BigInt temp(*this);
	temp += value;
	return temp;
}

BigInt& BigInt::operator += (const BigInt &value)
{
	if (m_data[0] != value.m_data[0])
	{
		int compare_value = CompareUnsigned(value);
		if (compare_value == 1)
		{
			Minus(value.m_data);
		}
		else if (compare_value == -1)
		{
			std::string temp = m_data;
			m_data = value.m_data;
			Minus(temp);
			m_data[0] = (value.m_data[0] == '-') ? '-' : '+';
		}
		else
		{
			m_data = "+0";
		}
	}
	else
	{
		Plus(value.m_data);
	}
	return *this;
}

BigInt BigInt::operator - (const BigInt &value)
{
	BigInt temp(*this);
	temp -= value;
	return temp;
}

BigInt& BigInt::operator -= (const BigInt &value)
{
	BigInt temp(value);
	temp.m_data[0] = (temp.m_data[0] == '+') ? '-' : '+';
	return operator += (temp);
}

BigInt BigInt::operator * (const BigInt &value)
{
	BigInt temp(*this);
	temp *= value;
	return temp;
}

BigInt& BigInt::operator *= (const BigInt &value)
{
	if (m_data == "+0" || value.m_data == "+0")
	{
		m_data = "+0";
		return *this;
	}
	char sign = (m_data[0] == value.m_data[0]) ? '+' : '-';

	m_data[0] = value.m_data[0];
	BigInt temp_sum_sum;
	for(int i = value.m_data.size() - 1 ; i > 0 ; --i)
	{
		// 此处可优化为1,2,4,8方式！！！
		BigInt temp_sum;
		for (int j = 0; j < (value.m_data[i] - '0'); ++j)
		{
			temp_sum.Plus(m_data);
		}

		for (int j = (value.m_data.size() - 1 - i); j > 0; --j)
		{
			temp_sum.m_data += "0";
		}

		temp_sum_sum += temp_sum;
	}
	m_data = temp_sum_sum.m_data;

	m_data[0] = sign;
	return *this;
}

BigInt BigInt::operator / (const BigInt &value)
{
	BigInt temp(*this);
	temp /= value;
	return temp;
}

BigInt& BigInt::operator /= (const BigInt &value)
{
	if (value.m_data == "+0")
	{
		assert(false);
		return *this;
	}

	if (m_data == "+0")
	{
		m_data_mode = "+0";
		return *this;
	}
	char sign = (m_data[0] == value.m_data[0]) ? '+' : '-';
	char mode_sign = m_data[0];

	if (CompareUnsigned(value) == -1)
	{
		m_data_mode = m_data;
		m_data = "+0";
		return *this;
	}
	else
	{
		BigInt divide(0);

		BigInt TEN(10);
		BigInt ZERO(0);

		m_data[0] = '+';
		BigInt positive_value(value);
		positive_value.m_data[0] = '+';
		while (true)
		{
			int ten_count = 0;
			BigInt temp_value(positive_value);
			while (true)
			{
				BigInt temp = temp_value * TEN;
				if (CompareUnsigned(temp) == -1)
				{
					break;
				}
				temp_value = temp;
				++ten_count;
			}

			BigInt temp_divide(0);
			BigInt temp_value_value(0);
			while (true)
			{
				temp_value_value += temp_value;
				if (CompareUnsigned(temp_value_value) == -1)
				{
					temp_value_value -= temp_value;
					break;
				}
				++temp_divide;
			}
			*this -= temp_value_value;

			if (ten_count > 0)
			{
				temp_divide.m_data.insert(temp_divide.m_data.end() , ten_count, '0');
			}
			divide += temp_divide;

			if (CompareUnsigned(positive_value) == -1)
			{
				break;
			}
		}

		m_data_mode = m_data;
		if (*this != ZERO)
		{
			m_data_mode[0] = mode_sign;
		}
		m_data = divide.m_data;
		m_data[0] = sign;
		return *this;
	}
}

BigInt BigInt::operator % (const BigInt &value)
{
	BigInt temp(*this);
	temp %= value;
	return temp;
}

BigInt& BigInt::operator %= (const BigInt &value)
{
	BigInt temp = *this / value;
	m_data = temp.m_data_mode;
	return *this;
}

BigInt& BigInt::operator ++ ()
{
	BigInt temp = 1;
	*this += temp;
	return *this;
}

BigInt& BigInt::operator -- ()
{
	BigInt temp = 1;
	*this -= temp;
	return *this;
}

BigInt BigInt::operator ++ (int)
{
	BigInt old = *this;
	BigInt temp = 1;
	*this += temp;
	return old;
}

BigInt BigInt::operator -- (int)
{
	BigInt old = *this;
	BigInt temp = 1;
	*this -= temp;
	return old;
}

bool BigInt::operator == (const BigInt &value)
{
	return (Compare(value) == 0);
}

bool BigInt::operator != (const BigInt &value)
{
	return (Compare(value) != 0);
}

bool BigInt::operator > (const BigInt &value)
{
	return (Compare(value) == 1);
}

bool BigInt::operator >= (const BigInt &value)
{
	return (Compare(value) >= 0);
}

bool BigInt::operator < (const BigInt &value)
{
	return (Compare(value) == -1);
}

bool BigInt::operator <= (const BigInt &value)
{
	return (Compare(value) <= 0);
}

//比较大小，>返回1，==返回0，<返回-1
int BigInt::Compare(const BigInt &value)
{
	if ((m_data[0] == '-') && (value.m_data[0] == '+'))
	{
		return -1;
	}
	else if ((m_data[0] == '+') && (value.m_data[0] == '-'))
	{
		return 1;
	}
	else if ((m_data[0] == '+') && (value.m_data[0] == '+'))
	{
		if (m_data.size() > value.m_data.size())
		{
			return 1;
		}
		else if (m_data.size() < value.m_data.size())
		{
			return -1;
		}
		else
		{
			if (m_data > value.m_data)
			{
				return 1;
			}
			else if (m_data < value.m_data)
			{
				return -1;
			}
			else
			{
				return 0;
			}
		}
	}
	else
	{
		if (m_data.size() < value.m_data.size())
		{
			return 1;
		}
		else if (m_data.size() > value.m_data.size())
		{
			return -1;
		}
		else
		{
			if (m_data < value.m_data)
			{
				return 1;
			}
			else if (m_data > value.m_data)
			{
				return -1;
			}
			else
			{
				return 0;
			}
		}
	}
}

int BigInt::CompareUnsigned(const BigInt &value)
{
	if (m_data.size() > value.m_data.size())
	{
		return 1;
	}
	else if (m_data.size() < value.m_data.size())
	{
		return -1;
	}
	else
	{
		std::string::size_type start = 1;
		if (m_data.substr(start , m_data.size() - 1) > value.m_data.substr(start , value.m_data.size() - 1))
		{
			return 1;
		}
		else if (m_data.substr(start , m_data.size() - 1) < value.m_data.substr(start , value.m_data.size() - 1))
		{
			return -1;
		}
		else
		{
			return 0;
		}
	}
}

void BigInt::Plus(const std::string &value)
{
	// 使得m_data长度大于value的长度
	std::string::size_type start = 1;
	if (m_data.size() < value.size())
	{
		m_data.insert(start , (value.size() - m_data.size()) , '0');
	}

	std::string::size_type i = m_data.size() - 1;
	std::string::size_type j = value.size() - 1;
	while (j > 1)
	{
		m_data[i] += (value[j] - '0');
		if (m_data[i] > '9')
		{
			m_data[i] -= 10;
			++m_data[i - 1];
		}
		--i;
		--j;
	}
	m_data[i] += (value[1] - '0');

	// 向前进位
	while ((i > 1) && (m_data[i] > '9'))
	{
		m_data[i] -= 10;
		--i;
		++m_data[i];
	}
	if (m_data[1] > '9')
	{
		m_data[1] -= 10;
		m_data.insert(start , 1 , '1');
	}
}

void BigInt::Minus(const std::string &value)
{
	// 此处一定有i >= j
	std::string::size_type i = m_data.size() - 1;
	std::string::size_type j = value.size() - 1;
	while (j > 0)
	{
		m_data[i] -= (value[j] - '0');
		// 借位
		if (m_data[i] < '0')
		{
			m_data[i] += 10;
			--m_data[i - 1];
		}
		--i;
		--j;
	}
	// 向前借位，第1位肯定够借，不用管
	while ((i > 1) && (m_data[i] < '0'))
	{
		m_data[i] += 10;
		--i;
		--m_data[i];
	}

	// 去掉前面的0
	std::string::size_type start = 1;
	std::string::size_type end = 1;
	for( ; ((end < m_data.size()) && (m_data[end] == '0')); ++end)
	{
		;
	}
	if (end > 1)
	{
		m_data.erase(start , end - 1);
	}
}

void BigInt::AddSign()
{
	if ((m_data[0] != '+') && (m_data[0] != '-'))
	{
		std::string::size_type start = 0;
		m_data.insert(start , 1 , '+');
	}
}
