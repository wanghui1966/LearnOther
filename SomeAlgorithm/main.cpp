#include "snow_flake.h"

int main()
{
	SnowFlake sf;
	sf.Init(3, 8);

	int64_t begin = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	for (int i = 0; i < 5000; ++i)
	{
		std::cout << sf.GetNextId() << std::endl;
	}
	int64_t end = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	std::cout << "begin=" << begin << ", end=" << end << std::endl;

	return 0;
}
