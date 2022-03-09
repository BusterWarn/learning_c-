CC = g++
CPPLAGS = -std=c++17 -O3 -Wextra -Werror

all:	sub

sub:	main.o nucelar_submarine.o
	$(CC) $(CPPLAGS) -o sub main.o nucelar_submarine.o

main.o: main.cpp nucelar_submarine.h
	$(CC) $(CPPLAGS) -c main.cpp

nucelar_submarine.o:	nucelar_submarine.cpp nucelar_submarine.h
	$(CC) $(CPPLAGS) -c nucelar_submarine.cpp

run:	sub
	./sub

valgrind:	main
	valgrind --leak-check=full --show-reachable=yes --track-origins=yes ./mish

clean:
	rm -f sub *.o core