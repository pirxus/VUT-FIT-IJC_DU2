#-------------------------------------------------
#  FILE:   Makefile
#  AUTHOR: Simon Sedlacek, FIT
#  EMAIL:  xsedla1h@stud.fit.vutbr.cz
#  DATE:   28.3.2019
#  BRIEF:  Makefile pro preklad druheho domaciho ukolu z predmetu IJC.
#  NOTE:   Reseni: IJC-DU2
#-------------------------------------------------
CFLAGS= -std=c99 -O2 -Wall -Wextra -pedantic -g
CPPFLAGS= -std=c++11 -O2 -Wall -Wextra -pedantic -g

now: wordcount wordcnt
all: tail2 tail wordcount

# Targets for tail2.cc
tail2: tail2.o
	g++ $(CPPFLAGS) $^ -o $@

tail2.o: tail2.cc
	g++ $(CPPFLAGS) -c $^


# Targets for tail.c
tail: tail.o
	gcc $(CFLAGS) $^ -o $@

tail.o: tail.c
	gcc $(CFLAGS) -c $^

# C wordcount
wordcount: htab.h wordcount.c io.c io.h libhtab.a
	gcc $(CFLAGS) $^ -o $@

wordcount.o: wordcount.c
	gcc $(CFLAGS) -c $^

io.o: io.c io.h
	gcc $(CFLAGS) -c $^

libhtab.a: htab_hash.o htab_init.o htab_move.o htab_size.o htab_bucket_count.o htab_free.o htab_clear.o htab_iterator_get.o
	ar -rcv $@ $^

# CPP wordcount
wordcnt: wordcnt.o
	g++ $(CPPFLAGS) $^ -o $@

wordcnt.o: wordcount.cc
	g++ $(CPPFLAGS) -c -o $@ $^




# Other targets
.PHONY: clean

clean:
	rm -f *.o tail tail2 wordcnt wordcount *.a *.so

# OBJECT FILES
htab_hash.o: htab_hash.c
	gcc $(CFLAGS) -c $^
htab_init.o: htab_init.c
	gcc $(CFLAGS) -c $^
htab_move.o: htab_move.c
	gcc $(CFLAGS) -c $^
htab_size.o: htab_size.c
	gcc $(CFLAGS) -c $^
htab_bucket_count.o: htab_bucket_count.c
	gcc $(CFLAGS) -c $^
htab_free.o: htab_free.c
	gcc $(CFLAGS) -c $^   
htab_clear.o: htab_clear.c
	gcc $(CFLAGS) -c $^
htab_iterator_get.o: htab_iterator_get.c
	gcc $(CFLAGS) -c $^

