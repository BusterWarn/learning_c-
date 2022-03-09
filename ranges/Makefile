CC = g++
CPPLAGS = -std=c++20 -O3 -Wextra -Werror

all:	ranges

ranges:	main.o
	$(CC) $(CPPLAGS) -o ranges main.o

main.o: main.cpp 
	$(CC) $(CPPLAGS) -c main.cpp

run:	ranges
	./ranges

valgrind:	main
	valgrind --leak-check=full --show-reachable=yes --track-origins=yes ./mish

clean:
	rm -f ranges *.o core