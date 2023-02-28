CXX=g++
CXXLAGS=-std=c++17 -Wconversion

normal:
	clang++ main.cpp -std=c++17 -Wconversion -I inc

quotes:
	clang++ main.cpp -std=c++17 -Wconversion -iquote inc

system: ${OBJ}
	clang++ main.cpp -std=c++17 -Wconversion -isystem inc -DISYSTEM