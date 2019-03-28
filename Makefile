#-------------------------------------------------
#  FILE:   Makefile
#  AUTHOR: Simon Sedlacek, FIT
#  EMAIL:  xsedla1h@stud.fit.vutbr.cz
#  DATE:   28.3.2019
#  BRIEF:  Makefile pro preklad druheho domaciho ukolu z predmetu IJC.
#  NOTE:   Reseni: IJC-DU2
#-------------------------------------------------
CFLAGS= -std=c99 -Wall -Wextra -pedantic -g
CPPFLAGS= -std=c++11 -Wall -Wextra -pedantic -g

all: tail2 #tail

# Targets for tail2.cc
tail2: tail2.o
	g++ $(CPPFLAGS) tail2.o -o tail2

tail2.o: tail2.cc
	g++ $(C{{FLAGS) -c -o tail2.o tail2.cc


# Targets for tail.c
tail: tail.o
	gcc $(CFLAGS) tail.o -o tail

tail.o: tail.c
	gcc $(CFLAGS) -c -o tail.o tail.c



# Other targets
.PHONY: clean

clean:
	rm -f *.o tail tail2

