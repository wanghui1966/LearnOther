#include <iostream>
#include <map>
#include <string>
#include <algorithm>

std::string str1;
std::string str2;
std::map<int, int> memo;	// i * 1000 + j
#define MEMO_KEY(i, j) ((i) * 1000 + j)

int MinDistance(int i, int j);
int GetMinDistance(int i, int j)
{
	int key = MEMO_KEY(i, j);
	auto it = memo.find(key);
	if (it != memo.end())
	{
		return it->second;
	}

	int min_distance = -1;
	if (i == -1)
	{
		min_distance = j + 1;
	}
	else if (j == -1)
	{
		min_distance = i + 1;
	}
	else
	{
		min_distance = MinDistance(i, j);
	}
	memo[key] = min_distance;
	return min_distance;
}
int MinDistance(int i, int j)
{
	if (i == -1 || j == -1)
	{
		return GetMinDistance(i, j);
	}

	if (str1[i] == str2[j])
	{
		return GetMinDistance(i - 1, j - 1);
	}
	else
	{
		return std::min(std::min(GetMinDistance(i, j - 1), GetMinDistance(i - 1, j)), GetMinDistance(i - 1, j - 1)) + 1;
	}
}

int MinDistance()
{
	int str1_length = str1.length();
	int str2_length = str2.length();
	for (int i = 1; i <= str1_length; ++i)
	{
		memo[MEMO_KEY(i, 0)] = i;
	}
	for (int j = 1; j <= str2_length; ++j)
	{
		memo[MEMO_KEY(0, j)] = j;
	}
	for (int i = 1; i <= str1_length; ++i)
	{
		for (int j = 1; j <= str2_length; ++j)
		{
			int key = MEMO_KEY(i, j);
			if (str1[i - 1] == str2[j - 1])
			{
				memo[key] = memo[MEMO_KEY(i - 1, j - 1)];
			}
			else
			{
				memo[key] = std::min(std::min(memo[MEMO_KEY(i, j - 1)], memo[MEMO_KEY(i - 1, j)]), memo[MEMO_KEY(i - 1, j - 1)]) + 1;
			}
		}
	}

	return memo[MEMO_KEY(str1_length, str2_length)];
}

int main()
{
	str1 = "rad";
	str2 = "apple";
	std::cout << "str1=" << str1 << ", str2=" << str2 << ", min_distance=" << MinDistance(str1.length() - 1, str2.length() - 1) << std::endl;
	memo.clear();
	std::cout << "str1=" << str1 << ", str2=" << str2 << ", min_distance=" << MinDistance() << std::endl;
	return 0;
}
