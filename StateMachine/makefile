
all:main
.PHONY:all

main:main.cpp MajiangRule.cpp GameState/*
	g++ main.cpp MajiangRule.cpp GameState/*.cpp -o main -std=c++11 -g

.PHONY:clean
clean:
	rm -f main
