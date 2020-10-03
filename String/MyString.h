#ifndef STRING_H
#define STRING_H

#include <iostream>

class MyString
{
	friend std::ostream& operator << (std::ostream& object, const MyString& myStr);
	friend std::istream& operator >> (std::istream& object, MyString& myStr);

public:
	MyString();
	MyString(const char *str);
	virtual ~MyString();
	MyString(const MyString& myStr);
	const MyString& operator = (const MyString& myStr);

protected:
	MyString(int length);

public:
	char& operator [] (int pos);
	const char& operator [] (int pos) const;

	MyString& operator + (const MyString& myStr);
	MyString& operator += (const MyString& myStr);

	bool operator > (const MyString& myStr);
	bool operator >= (const MyString& myStr);
	bool operator < (const MyString& myStr);
	bool operator <= (const MyString& myStr);
	bool operator == (const MyString& myStr);
	bool operator != (const MyString& myStr);

	int Length() const;
	int Capacity() const;

protected:
	int m_length = 0;				// 实际长度
	int m_capacity = 0;				// 大小
	char *m_data = nullptr;
};

#endif
