#include <iostream>
#include <cstring>
#include <iomanip>
#include <cassert>
#include <cstdlib>
#include <cmath>

#include "MyString.h"

static int GetCapacityByLength(int length)
{
	length += 1;
	if (length < 2)
	{
		return 1;
	}
	else
	{
		return std::pow(2, std::ceil((1.0f * std::log(length)) / std::log(2)));
	}
}

MyString::MyString()
{
	m_length = 0;
	m_capacity = GetCapacityByLength(m_length);
	m_data = (char*)calloc(m_capacity, sizeof(char));
}

MyString::MyString(const char *str)
{
	m_length = 0;
	if (str == nullptr)
	{
		m_capacity = GetCapacityByLength(m_length);
		m_data = (char*)calloc(m_capacity, sizeof(char));
	}
	else
	{
		m_length = strlen(str);
		m_capacity = GetCapacityByLength(m_length);
		m_data = (char*)calloc(m_capacity, sizeof(char));
		strcpy(m_data, str);
	}
}

MyString::~MyString()
{
	m_length = 0;
	m_capacity = 0;
	free(m_data);
	m_data = nullptr;
}

MyString::MyString(const MyString& str)
{
	m_length = str.m_length;
	m_capacity = str.m_capacity;
	m_data = (char*)calloc(m_capacity, sizeof(char));
	strcpy(m_data, str.m_data);
}

const MyString& MyString::operator=(const MyString& str)
{
	if (this == &str)
	{
		return *this;
	}

	delete []m_data;
	m_length = str.m_length;
	m_capacity = str.m_capacity;
	m_data = (char*)calloc(m_capacity, sizeof(char));
	strcpy(m_data, str.m_data);
	return *this;
}

MyString::MyString(int length)
{
	m_length = length;
	m_capacity = GetCapacityByLength(m_length);
	m_data = (char*)calloc(m_capacity, sizeof(char));
}

char& MyString::operator[](int pos)
{
	assert((pos >= 0) && (pos < m_length));
	return m_data[pos];

}

const char& MyString::operator[](int pos) const
{
	assert((pos >= 0) && (pos < m_length));
	return m_data[pos];
}

MyString& MyString::operator+(const MyString& str)
{
	if (str.m_length == 0)
	{
		return *this;
	}
	else
	{
		MyString *temp = new MyString(m_length + str.m_length);
		strcpy(temp->m_data, m_data);
		strcat(temp->m_data, str.m_data);
		return *temp;
	}
}

MyString& MyString::operator+=(const MyString& str)
{
	if (str.m_length == 0)
	{
		return *this;
	}
	m_length += str.m_length;
	m_capacity = GetCapacityByLength(m_length);
	m_data = (char*)realloc(m_data, sizeof(char) * m_capacity);
	strcat(m_data, str.m_data);
	return *this;
}

bool MyString::operator>(const MyString& str)
{
	return (strcmp(m_data, str.m_data) > 0);
}

bool MyString::operator>=(const MyString& str)
{
	return (strcmp(m_data, str.m_data) >= 0);
}

bool MyString::operator<(const MyString& str)
{
	return (strcmp(m_data, str.m_data) < 0);
}

bool MyString::operator<=(const MyString& str)
{
	return (strcmp(m_data, str.m_data) <= 0);
}

bool MyString::operator==(const MyString& str)
{
	return (strcmp(m_data, str.m_data) == 0);
}

bool MyString::operator!=(const MyString& str)
{
	return (strcmp(m_data, str.m_data) != 0);
}

int MyString::Length() const
{
	return m_length;
}

int MyString::Capacity() const
{
	return m_capacity;
}

std::istream& operator>>(std::istream& object, MyString& str)
{
	object >> str.m_data;
	return object;
}

std::ostream& operator<<(std::ostream& object, const MyString& str)
{
	object << str.m_data;
	return object;
}
