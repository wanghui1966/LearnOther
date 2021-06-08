#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <limits.h>

std::vector<int> coins;
std::map<int, int> memo;

int MinCoins(int mount)
{
	if (mount == 0)
	{
		return 0;
	}
	if (mount < 0)
	{
		return INT_MAX;
	}

	int result = INT_MAX;
	for (int i = 0; i < coins.size(); ++i)
	{
		int min_coins = INT_MAX;
		auto it = memo.find(mount - coins[i]);
		if (it != memo.end())
		{
			min_coins = it->second;
		}
		else
		{
			min_coins = MinCoins(mount - coins[i]);
		}
		if (min_coins == INT_MAX)
		{
			continue;
		}

		result = std::min(result, min_coins + 1);
	}

	memo[mount] = result;
	return result;
}

int main()
{
	coins.push_back(2);
	coins.push_back(5);
	coins.push_back(10);
	std::cout << "coins=";
	for (int i = 0; i < coins.size(); ++i)
	{
		std::cout << coins[i] << ",";
	}
	std::cout << std::endl;

	for (int i = 1; i < 20; ++i)
	{
		std::cout << "mount=" << i << ", min_coins=" << MinCoins(i) << std::endl;
	}
	return 0;
}
