#ifndef BIGINT_H
#define BIGINT_H

#include <iostream>
#include <string>

// 使用std::string实现的大整数类，支持加、减、乘、除、取模、前置和后置++、前置和后置--、各种比较、输入、输出运算
class BigInt
{
public:
	BigInt();
	BigInt(int32_t value);
	BigInt(uint32_t value);
	BigInt(int64_t value);
	BigInt(uint64_t value);
	BigInt(const std::string &value);
	virtual ~BigInt();
	BigInt(const BigInt &value);

	BigInt& operator = (const BigInt &value);
	BigInt& operator = (int32_t value);
	BigInt& operator = (uint32_t value);
	BigInt& operator = (int64_t value);
	BigInt& operator = (uint64_t value);

public:
	friend std::istream& operator >> (std::istream &object , BigInt &value);
	friend std::ostream& operator << (std::ostream &object , const BigInt &value);

	// 加减乘除取模符号重载的时候不能返回引用，如果用引用就必须new，这样就没有地方delete，会出问题
	BigInt operator + (const BigInt &value);
	BigInt& operator += (const BigInt &value);
	BigInt operator - (const BigInt &value);
	BigInt& operator -= (const BigInt &value);
	BigInt operator * (const BigInt &value);
	BigInt& operator *= (const BigInt &value);
	BigInt operator / (const BigInt &value);
	BigInt& operator /= (const BigInt &value);
	BigInt operator % (const BigInt &value);
	BigInt& operator %= (const BigInt &value);

	BigInt& operator ++ ();
	BigInt& operator -- ();
	BigInt operator ++ (int);
	BigInt operator -- (int);

	bool operator == (const BigInt &value);
	bool operator != (const BigInt &value);
	bool operator > (const BigInt &value);
	bool operator >= (const BigInt &value);
	bool operator < (const BigInt &value);
	bool operator <= (const BigInt &value);

protected:
	int Compare(const BigInt &value);
	int CompareUnsigned(const BigInt &value);

	// 无符号的加法
	void Plus(const std::string &value);

	// 无符号的减法，一定是绝对值大的减去绝对值小的
	void Minus(const std::string &value);

	//如果手动输入的数字没有符号，则加上+号
	void AddSign();

protected:
	std::string m_data;

	// 除法的临时数据，取模的时候用
	std::string m_data_mode;
};

#endif
