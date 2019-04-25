#-------------------------------------------------
#  FILE:   Makefile
#  AUTHOR: Simon Sedlacek, FIT
#  EMAIL:  xsedla1h@stud.fit.vutbr.cz
#  DATE:   14.4.2019
#  BRIEF:  Makefile pro preklad druheho domaciho ukolu z predmetu IJC.
#  NOTE:   Reseni: IJC-DU2
#-------------------------------------------------
CPPFLAGS= -std=c++11 -O2 -Wall -Wextra -pedantic -g
CFLAGS= -std=c99 -O2 -Wall -Wextra -pedantic -g

all: tail tail2 wordcount wordcount-dynamic
static: wordcount
dynamic: wordcount-dynamic


#-------------------------------------------------
# WORDCOUNT
#-------------------------------------------------

# C wordcount static
wordcount: htab.h wordcount.c io.c io.h libhtab.a	
	ranlib libhtab.a
	gcc $(CFLAGS) -static wordcount.c io.c -L. -lhtab -o $@

# C wordcount dynamic
wordcount-dynamic: htab.h wordcount.c io.c io.h libhtab.so
	gcc $(CFLAGS) wordcount.c io.c -L. -lhtab -o $@


# CPP wordcount
wordcnt: wordcnt.o
	g++ $(CPPFLAGS) $^ -o $@

wordcnt.o: wordcnt.cc
	g++ $(CPPFLAGS) -c -o $@ $^


#-------------------------------------------------
# TAIL
#-------------------------------------------------

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


#-------------------------------------------------
# OTHER 
#-------------------------------------------------

.PHONY: clean
clean:
	rm -f *.o tail tail2 wordcnt wordcount wordcount-dynamic *.a *.so


#-------------------------------------------------
# OBJECT 
#-------------------------------------------------

# static
htab_hash.o: htab_hash.c htab_private.h
	gcc $(CFLAGS) -c $<
htab_init.o: htab_init.c htab_private.h
	gcc $(CFLAGS) -c $<
htab_move.o: htab_move.c htab_private.h
	gcc $(CFLAGS) -c $<
htab_size.o: htab_size.c htab_private.h
	gcc $(CFLAGS) -c $<
htab_bucket_count.o: htab_bucket_count.c htab_private.h
	gcc $(CFLAGS) -c $<
htab_free.o: htab_free.c htab_private.h
	gcc $(CFLAGS) -c $<   
htab_clear.o: htab_clear.c htab_private.h
	gcc $(CFLAGS) -c $<
htab_iterator_value.o: htab_iterator_value.c htab_private.h
	gcc $(CFLAGS) -c $<
htab.o: htab.c htab_private.h
	gcc $(CFLAGS) -c $<
htab_iterator_next.o: htab_iterator_next.c htab_private.h
	gcc $(CFLAGS) -c $<
htab_iterator_begin.o: htab_iterator_begin.c htab_private.h
	gcc $(CFLAGS) -c $<
htab_iterator_end.o: htab_iterator_end.c htab_private.h
	gcc $(CFLAGS) -c $<
htab_iterator_get_key.o: htab_iterator_get_key.c htab_private.h
	gcc $(CFLAGS) -c $<
htab_lookup_add.o: htab_lookup_add.c htab_private.h
	gcc $(CFLAGS) -c $<

# dynamic
htab_hash-s.o: htab_hash.c htab_private.h
	gcc $(CFLAGS) -fPIC -c $< -o $@
htab_init-s.o: htab_init.c htab_private.h
	gcc $(CFLAGS) -fPIC -c $< -o $@
htab_move-s.o: htab_move.c htab_private.h
	gcc $(CFLAGS) -fPIC -c $< -o $@
htab_size-s.o: htab_size.c htab_private.h
	gcc $(CFLAGS) -fPIC -c $< -o $@
htab_bucket_count-s.o: htab_bucket_count.c htab_private.h
	gcc $(CFLAGS) -fPIC -c $< -o $@
htab_free-s.o: htab_free.c htab_private.h
	gcc $(CFLAGS) -fPIC -c $< -o $@
htab_clear-s.o: htab_clear.c htab_private.h
	gcc $(CFLAGS) -fPIC -c $< -o $@
htab_iterator_value-s.o: htab_iterator_value.c htab_private.h
	gcc $(CFLAGS) -fPIC -c $< -o $@
htab-s.o: htab.c htab_private.h
	gcc $(CFLAGS) -fPIC -c $< -o $@
htab_iterator_next-s.o: htab_iterator_next.c htab_private.h
	gcc $(CFLAGS) -fPIC -c $< -o $@
htab_iterator_begin-s.o: htab_iterator_begin.c htab_private.h
	gcc $(CFLAGS) -fPIC -c $< -o $@
htab_iterator_end-s.o: htab_iterator_end.c htab_private.h
	gcc $(CFLAGS) -fPIC -c $< -o $@
htab_iterator_get_key-s.o: htab_iterator_get_key.c htab_private.h
	gcc $(CFLAGS) -fPIC -c $< -o $@
htab_lookup_add-s.o: htab_lookup_add.c htab_private.h
	gcc $(CFLAGS) -fPIC -c $< -o $@


#-------------------------------------------------
# LIBRARIES 
#-------------------------------------------------

# static
libhtab.a: htab_hash.o htab_init.o htab_move.o htab_size.o htab_bucket_count.o htab_free.o htab_clear.o htab.o htab_iterator_value.o htab_iterator_next.o htab_iterator_begin.o htab_iterator_end.o htab_iterator_get_key.o htab_lookup_add.o
	ar rcv $@ $^

# dynamic
libhtab.so: htab_hash-s.o htab_init-s.o htab_move-s.o htab_size-s.o htab_bucket_count-s.o htab_free-s.o htab_clear-s.o htab-s.o htab_iterator_value-s.o htab_iterator_next-s.o htab_iterator_begin-s.o htab_iterator_end-s.o htab_iterator_get_key-s.o htab_lookup_add-s.o
	gcc $(CFLAGS) -shared -o $@ $^
