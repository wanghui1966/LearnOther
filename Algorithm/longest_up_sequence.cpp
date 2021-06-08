#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <limits.h>

int LongestUpSequenceN2(const std::vector<int> &data)
{
	int data_size = data.size();
	if (data_size == 0)
	{
		return 0;
	}
	if (data_size == 1)
	{
		return 1;
	}

	std::vector<int> result(data_size, 1);
	for (int i = 0; i < data_size; ++i)
	{
		for (int j = 0; j < i; ++j)
		{
			if (data[i] > data[j])
			{
				result[i] = std::max(result[i], result[j] + 1);
			}
		}
	}

	return result[data_size - 1];
}

int LongestUpSequenceStack(const std::vector<int> &data)
{
	int data_size = data.size();
	if (data_size == 0)
	{
		return 0;
	}
	if (data_size == 1)
	{
		return 1;
	}

	// 辅助栈
	std::vector<int> result(data_size, 0);
	result[0] = data[0];
	int len = 0;
	for(int i = 1; i< data_size; i++)
	{
		// 若不小于当前最长上升子系列最后一个数，直接加入
		if (data[i] >= result[len])
		{
			result[++len] = data[i];
			continue;
		}

		int left = 0, right = len, mid = 0;
		// 否则，二分法找到当前最长子系列中最后一个不大于它的数，替代它
		while (left <= right)
		{
			mid = (left + right) / 2;
			if (data[i] < result[mid])
			{
				right = mid - 1;
			}
			else
			{
				left = mid + 1;
			}
		}
		result[mid] = data[i];
	}
	return len + 1;
}

int main()
{
	std::vector<int> seq;
	seq.push_back(1);
	seq.push_back(5);
	seq.push_back(8);
	seq.push_back(3);
	seq.push_back(6);
	seq.push_back(7);
	for (int i = 0; i < seq.size(); ++i)
	{
		std::cout << seq[i] << ", ";
	}
	std::cout << std::endl;
	std::cout << "LongestUpSequenceN2=" << LongestUpSequenceN2(seq) << ", LongestUpSequenceStack=" << LongestUpSequenceStack(seq) << std::endl;
	return 0;
}
