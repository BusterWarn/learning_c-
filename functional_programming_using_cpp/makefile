CXX=clang++
CXXFLAGS=-std=c++17 -Wall -Wextra -Wpedantic -Wconversion
INCLUDES=-isystem lib/ build/catch2.o

build/catch2.o: lib/catch_amalgamated.hpp
	$(CXX) -c -o build/catch2.o lib/catch_amalgamated.cpp
