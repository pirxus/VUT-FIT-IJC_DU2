#-------------------------------------------------
#  FILE:   Makefile
#  AUTHOR: Simon Sedlacek, FIT
#  EMAIL:  xsedla1h@stud.fit.vutbr.cz
#  DATE:   28.3.2019
#  BRIEF:  Makefile pro preklad druheho domaciho ukolu z predmetu IJC.
#  NOTE:   Reseni: IJC-DU2
#-------------------------------------------------
CFLAGS= -std=c99 -Wall -Wextra -pedantic -g
CPPFLAGS= -std=c++11 -O2 -Wall -Wextra -pedantic -g

now: wordcnt wordcount
all: tail2 tail wordcount

# Targets for tail2.cc
tail2: tail2.o
	g++ $(CPPFLAGS) tail2.o -o tail2

tail2.o: tail2.cc
	g++ $(CPPFLAGS) -c -o tail2.o tail2.cc


# Targets for tail.c
tail: tail.o
	gcc $(CFLAGS) tail.o -o tail

tail.o: tail.c
	gcc $(CFLAGS) -c -o tail.o tail.c

# C wordcount
wordcount: wordcount.o io.o
	gcc $(CFLAGS) wordcount.o io.o -o wordcount

wordcount.o: wordcount.c
	gcc $(CFLAGS) -c -o wordcount.o wordcount.c

io.o: io.c io.h
	gcc $(CFLAGS) -c -o io.o io.c

# CPP wordcount
wordcnt: wordcnt.o
	g++ $(CPPFLAGS) wordcnt.o -o wordcnt

wordcnt.o: wordcount.cc
	g++ $(CPPFLAGS) -c -o wordcnt.o wordcount.cc




# Other targets
.PHONY: clean

clean:
	rm -f *.o tail tail2 wordcnt wordcount

