/**
 *	@file	htab_clear.c
 *	@author	Simon Sedlacek, FIT
 *	@date	5.4.2019
 *	@note	Reseni: IJC-DU2, priklad 2)
 *	Prelozeno: gcc 8.3.1 - Fedora release 29 (Twenty Nine) x86_64 
 */

#include <stdlib.h>
#include "htab.h"
#include "htab_private.h"

void htab_clear(htab_t *t) {
    if (t == NULL)
        return;

    struct htab_item *next;

    for (size_t i = 0; i < t->arr_size; i++) {

        /* Uvolnime obsah kazdeho radku tabulky
         * a nasledne radek samotny */
        while (t->array[i] != NULL) {
            next = t->array[i]->next;
            free(t->array[i]->key);
            free(t->array[i]);
            t->array[i] = next;
        }
    }

    t->size = 0;
}
