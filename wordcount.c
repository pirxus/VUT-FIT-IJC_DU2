/**
 *	@file	wordcount.c
 *	@author	Simon Sedlacek, FIT
 *	@date	11.4.2019
 *	@note	Reseni: IJC-DU2, priklad 2)
 *	Prelozeno: gcc 8.3.1 - Fedora release 29 (Twenty Nine) x86_64 
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "io.h"
#include "htab.h"


#define WORD_LIMIT 128
#define ARRAY_SIZE 100
#define NEW_ARRAY_SIZE 200 

int main(void) {

    char s[WORD_LIMIT] = {0};
    int count = 0;
    bool print_warning = true;

    htab_iterator_t iterator;
    htab_t *table = htab_init(ARRAY_SIZE);
    if (table == NULL)
        return 1;

    /* Nacteme slova do tabulky */
    while ((count = get_word(s, WORD_LIMIT, stdin)) != EOF) {

        if (count >= WORD_LIMIT && print_warning == true) {
            print_warning = false;
            fprintf(stderr, "Warning: Slovo prekrocilo limit delky slova, "
                    "dalsi slova jsou potencialne zkracena\n");
        }

        iterator = htab_lookup_add(table, s);
        if (!htab_iterator_valid(iterator)) {
            htab_free(table);
            return 1;
        }

        htab_iterator_set_value(iterator, htab_iterator_get_value(iterator) + 1);
    }

#ifdef TEST
    /* Test migrace tabulky do nove tabulky s jinou velikosti */

    htab_t *new = htab_move(NEW_ARRAY_SIZE, table);

    if (new == NULL) {
        htab_free(table);
        return 1;
    }

    htab_free(table);
    table = new;

#endif

    /* Vypiseme slova a pocty */
    for (iterator = htab_begin(table);
            htab_iterator_valid(iterator);
            iterator = htab_iterator_next(iterator)) {
        
        printf("%s    %d\n",
               htab_iterator_get_key(iterator),
               htab_iterator_get_value(iterator));
    }

    htab_free(table);
    return 0;
}
