CXX=g++
CXXFLAGS=-g -Wall -Wextra -Werror -Wpedantic -Wreturn-type \
         -Wparentheses -Wunused -Wundef -Wshadow -Wswitch-default -Wunreachable-code

with_20:
	${CXX} --std=c++20 main.cpp ${CXXFLAGS}

with_17:
	${CXX} --std=c++17 main.cpp ${CXXFLAGS}

clean :
	rm -rf a.out