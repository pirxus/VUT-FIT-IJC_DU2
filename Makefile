CFLAGS= -std=c99 -Wall -Wextra -pedantic -g

tail: tail.o
	gcc $(CFLAGS) tail.o -o tail

tail.o: tail.c
	gcc $(CFLAGS) -c -o tail.o tail.c

.PHONY: clean

clean:
	rm -f *.o tail

