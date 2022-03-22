CC = g++
CPPLAGS = -std=c++20 -O3 -Wextra -Werror

all:	exe

exe:	main.o my_class.o
	$(CC) $(CPPLAGS) -o exe main.o my_class.o

main.o: main.cpp my_class.h
	$(CC) $(CPPLAGS) -c main.cpp

my_class.o: my_class.cpp  my_class.h
	$(CC) $(CPPLAGS) -c my_class.cpp

run:	exe
	./exe

valgrind:	main
	valgrind --leak-check=full --show-reachable=yes --track-origins=yes ./mish

clean:
	rm -f exe *.o core