#include "MyString.h"

void Output(const MyString &str)
{
	std::cout << "str=" << str << ", lenght=" << str.Length() << ", size=" << str.Capacity() << std::endl;
}

#define Compare(str1, str2) \
	std::cout << std::endl; \
	std::cout << "str1=" << str1 << ", str2=" << str2 << std::endl; \
	std::cout << "(str1 >  str2) = " << (str1 > str2) << ", "; \
	std::cout << "(str1 >= str2) = " << (str1 >= str2) << ", "; \
	std::cout << "(str1 <  str2) = " << (str1 < str2) << ", "; \
	std::cout << "(str1 <= str2) = " << (str1 <= str2) << ", "; \
	std::cout << "(str1 != str2) = " << (str1 != str2) << ", "; \
	std::cout << "(str1 == str2) = " << (str1 == str2) << ", "; \
	std::cout << std::endl;

int main()
{
	MyString str;
	Output(str);

	str += "abc";
	Output(str);

	str = str + "abc";
	Output(str);

	MyString str2 = str;
	Compare(str, str2);

	str2[2] = 'C';
	Compare(str, str2);

	for (int i = 0; i < 10; ++i)
	{
		str += "def";
		Output(str);
	}

	return 0;
}
