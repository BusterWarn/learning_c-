CC = g++
CPPLAGS = -std=c++20 -O3 -Wextra -Werror

all:	exe

exe:	main.o dogoo.o
	$(CC) $(CPPLAGS) -o exe main.o dogoo.o

main.o: main.cpp dogoo.h
	$(CC) $(CPPLAGS) -c main.cpp

dogoo.o: dogoo.cpp  dogoo.h
	$(CC) $(CPPLAGS) -c dogoo.cpp

run:	exe
	./exe

valgrind:	main
	valgrind --leak-check=full --show-reachable=yes --track-origins=yes ./mish

clean:
	rm -f exe *.o core