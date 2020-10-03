#include <iostream>
#include "BigInt.h"

void TestCommon(int64_t i1, int64_t i2)
{
	BigInt b1 = i1;
	BigInt b2 = i2;

	std::cout << "i1=" << i1 << ", i2=" << i2 << ", i1+i2=" << (i1 + i2) << ", i1-i2=" << (i1 - i2) << ", i2 - i1 = " << (i2 - i1) << ", i1*i2=" << (i1 * i2) << ", i1/i2=" << (i1 / i2) << ", ++i1=" << (++i1) << ", i1++=" << (i1++) << ", --i1=" << (--i1) << ", i1--=" << (i1--) << std::endl;
	std::cout << "b1=" << b1 << ", b2=" << b2 << ", b1+b2=" << (b1 + b2) << ", b1-b2=" << (b1 - b2) << ", b2 - b1 = " << (b2 - b1) << ", b1*b2=" << (b1 * b2) << ", b1/b2=" << (b1 / b2) << ", ++b1=" << (++b1) << ", b1++=" << (b1++) << ", --b1=" << (--b1) << ", b1--=" << (b1--) << std::endl << std::endl;
}

void TestPlus(int64_t i1, int64_t i2)
{
	BigInt b1 = i1;
	BigInt b2 = i2;

	std::cout << "i1=" << i1 << ", i2=" << i2;
	i1 += i2;
	std::cout << ", (i1+=i2), i1=" << i1 << std::endl;

	std::cout << "b1=" << b1 << ", b2=" << b2;
	b1 += b2;
	std::cout << ", (b1+=b2), b1=" << i1 << std::endl << std::endl;
}

void TestMinus(int64_t i1, int64_t i2)
{
	BigInt b1 = i1;
	BigInt b2 = i2;

	std::cout << "i1=" << i1 << ", i2=" << i2;
	i1 -= i2;
	std::cout << ", (i1-=i2), i1=" << i1 << std::endl;

	std::cout << "b1=" << b1 << ", b2=" << b2;
	b1 -= b2;
	std::cout << ", (b1-=b2), b1=" << i1 << std::endl << std::endl;
}

void TestMultiply(int64_t i1, int64_t i2)
{
	BigInt b1 = i1;
	BigInt b2 = i2;

	std::cout << "i1=" << i1 << ", i2=" << i2;
	i1 *= i2;
	std::cout << ", (i1*=i2), i1=" << i1 << std::endl;

	std::cout << "b1=" << b1 << ", b2=" << b2;
	b1 *= b2;
	std::cout << ", (b1*=b2), b1=" << i1 << std::endl << std::endl;
}

void TestDivide(int64_t i1, int64_t i2)
{
	BigInt b1 = i1;
	BigInt b2 = i2;

	std::cout << "i1=" << i1 << ", i2=" << i2;
	i1 /= i2;
	std::cout << ", (i1 /= i2), i1=" << i1 << std::endl;

	std::cout << "b1=" << b1 << ", b2=" << b2;
	b1 /= b2;
	std::cout << ", (b1 /= b2), b1=" << i1 << std::endl << std::endl;
}

void TestMod(int64_t i1, int64_t i2)
{
	BigInt b1 = i1;
	BigInt b2 = i2;

	std::cout << "i1=" << i1 << ", i2=" << i2;
	i1 %= i2;
	std::cout << ", (i1 %= i2), i1=" << i1 << std::endl;

	std::cout << "b1=" << b1 << ", b2=" << b2;
	b1 %= b2;
	std::cout << ", (b1 %= b2), b1=" << i1 << std::endl << std::endl;
}

bool TestRandom()
{
	for (int i = -100; i < 100; ++i)
	{
		for (int j = -100; j < 100; ++j)
		{
			BigInt b1 = i;
			BigInt b2 = j;

			if ((i > j) != (b1 > b2))
			{
				std::cout << "TestRandom(" << i << ">" << j << ") fail" << std::endl;
				return false;
			}

			if ((i >= j) != (b1 >= b2))
			{
				std::cout << "TestRandom(" << i << ">=" << j << ") fail" << std::endl;
				return false;
			}

			if ((i < j) != (b1 < b2))
			{
				std::cout << "TestRandom(" << i << "<" << j << ") fail" << std::endl;
				return false;
			}

			if ((i <= j) != (b1 <= b2))
			{
				std::cout << "TestRandom(" << i << "<=" << j << ") fail" << std::endl;
				return false;
			}

			if ((i == j) != (b1 == b2))
			{
				std::cout << "TestRandom(" << i << "==" << j << ") fail" << std::endl;
				return false;
			}

			if ((i != j) != (b1 != b2))
			{
				std::cout << "TestRandom(" << i << "!=" << j << ") fail" << std::endl;
				return false;
			}

			if (BigInt(i + j) != b1 + b2)
			{
				std::cout << "TestRandom(" << i << "+" << j << ") fail" << std::endl;
				return false;
			}

			int k = i;
			k += j;
			BigInt b3 = i;
			b3 += b2;
			if (BigInt(k) != b3)
			{
				std::cout << "TestRandom(" << i << "+=" << j << ") fail" << std::endl;
				return false;
			}

			if (BigInt(i - j) != b1 - b2)
			{
				std::cout << "TestRandom(" << i << "-" << j << ") fail" << std::endl;
				return false;
			}

			k = i;
			k -= j;
			b3 = i;
			b3 -= b2;
			if (BigInt(k) != b3)
			{
				std::cout << "TestRandom(" << i << "-=" << j << ") fail" << std::endl;
				return false;
			}

			if (BigInt(i * j) != b1 * b2)
			{
				std::cout << "TestRandom(" << i << "*" << j << ") fail" << std::endl;
				return false;
			}

			k = i;
			k *= j;
			b3 = i;
			b3 *= b2;
			if (BigInt(k) != b3)
			{
				std::cout << "TestRandom(" << i << "*=" << j << ") fail" << std::endl;
				return false;
			}

			if (j != 0)
			{
				if (BigInt(i / j) != b1 / b2)
				{
					std::cout << "TestRandom(" << i << "/" << j << ") fail" << std::endl;
					return false;
				}

				k = i;
				k /= j;
				b3 = i;
				b3 /= b2;
				if (BigInt(k) != b3)
				{
					std::cout << "TestRandom(" << i << "/=" << j << ") fail" << std::endl;
					return false;
				}

				if (BigInt(i % j) != b1 % b2)
				{
					std::cout << "TestRandom(" << i << "%" << j << ") fail" << std::endl;
					return false;
				}

				k = i;
				k %= j;
				b3 = i;
				b3 %= b2;
				if (BigInt(k) != b3)
				{
					std::cout << "TestRandom(" << i << "%=" << j << ") fail" << std::endl;
					return false;
				}
			}
		}
	}

	std::cout << "TestRandom success" << std::endl << std::endl;
	return true;
}

int main()
{
	TestRandom();

	int64_t i1 = 42586998;
	int64_t i2 = 674785476;
	TestCommon(i1, i2);
	TestPlus(i1, i2);
	TestMinus(i1, i2);
	TestMultiply(i1, i2);
	TestDivide(i1, i2);
	TestMod(i1, i2);

	i1 *= (-1);
	TestCommon(i1, i2);
	TestPlus(i1, i2);
	TestMinus(i1, i2);
	TestMultiply(i1, i2);
	TestDivide(i1, i2);
	TestMod(i1, i2);

	i2 *= (-1);
	TestCommon(i1, i2);
	TestPlus(i1, i2);
	TestMinus(i1, i2);
	TestMultiply(i1, i2);
	TestDivide(i1, i2);
	TestMod(i1, i2);

	return 0;
}
