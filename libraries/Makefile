CXX=g++
CXXFLAGS=-std=c++20 -g -Wall -Wextra -Werror -Wpedantic -Wreturn-type \
         -Wparentheses -Wunused -Wundef -Wshadow -Wswitch-default -Wunreachable-code

# Static library files
test_with_static_library:	test/test.cpp library_static
	${CXX} test/test.cpp ${CXXFLAGS} -iquote power_of -B out -L. -lpower_of_static -o out/test_from_static.exe

library_static: object
	ar rcs out/libpower_of_static.a out/power_of.o

# Dynamic library files
run_test_with_dynamic_library: test_with_dynamic_library
	LD_LIBRARY_PATH="${CURDIR}/out" ./out/test_from_dynamic.exe

test_with_dynamic_library:	test/test.cpp library_dynamic
	${CXX} test/test.cpp ${CXXFLAGS} -iquote power_of -B out -L. -lpower_of_dynamic -o out/test_from_dynamic.exe

library_dynamic: power_of/power_of.cpp power_of/power_of.h
	mkdir -p out
	$(CXX) power_of/power_of.cpp ${CXXFLAGS} -fPIC -shared -lc -o out/libpower_of_dynamic.so

# Object files
test_with_object_library:	test/test.cpp object
	${CXX} test/test.cpp out/power_of.o ${CXXFLAGS} -iquote power_of -o out/test_from_object.exe

object: power_of/power_of.cpp power_of/power_of.h
	mkdir -p out
	${CXX} ${CXXFLAGS} -c power_of/power_of.cpp -o out/power_of.o

clean :
	rm -rf out