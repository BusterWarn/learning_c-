CXX=clang++
CXXLAGS=-std=c++20 -fmodules-ts
CXXLAGS_OLD=-std=c++20 -fmodules -stdlib=libc++ -isystemC:\Users\xxhulthb\Documents\git\llvm-project\libcxx\include

main: main.cpp module
	${CXX} ${CXXLAGS} -o main -fprebuilt-module-path=. main.cpp hello.cpp

module: hello.cpp
	${CXX} ${CXXLAGS} -o hello.pcm --precompile -x c++-module hello.cpp

clean:
	rm hello.main
	rm hello.pcm