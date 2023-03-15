CXX=clang++
CXXLAGS=-std=c++20 -fmodules-ts
CXXLAGS_OLD=-std=c++20 -fmodules -stdlib=libc++ -isystemC:\Users\xxhulthb\Documents\git\llvm-project\libcxx\include

one: main.cpp
	${CXX} main.cpp ${CXXLAGS} -o main

main: main.cpp
	${CXX} ${CXXLAGS} -o main -fprebuilt-module-path=. main.cpp hello.cpp

module: hello.cpp
	${CXX} ${CXXLAGS} -o hello.pcm --precompile -x c++-module hello.cpp

	