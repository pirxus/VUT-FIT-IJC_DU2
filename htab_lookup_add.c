/**
 *	@file	htab_lookup_add.c
 *	@author	Simon Sedlacek, FIT
 *	@date	14.4.2019
 *	@note	Reseni: IJC-DU2, priklad 2)
 *	Prelozeno: gcc 8.3.1 - Fedora release 29 (Twenty Nine) x86_64 
 */

#include <stdlib.h>
#include "htab.h"
#include "htab_private.h"

htab_iterator_t htab_lookup_add(htab_t *t, const char *key) {
    if (t == NULL || key == NULL) {
        fprintf(stderr, "Error: tabulka nebo klic neexistuji\n");
        return htab_end(t);
    }

    int index = (htab_hash_function(key) % t->arr_size);
    htab_iterator_t it = { .ptr = t->array[index], .t = t, .idx = index };

    /* Projdeme cely seznam na danem indexu a zjistime, zda se v tabulce jiz
     * dane slovo nachazi */
    while (htab_iterator_valid(it) && it.idx == index) {
        if (!strcmp(htab_iterator_get_key(it), key)) {
            return it;
        }

        it = htab_iterator_next(it);
    }

    /* Tabulka danou polozku neobsahovala, tudiz musime polozku pridat */
    it.ptr = malloc(sizeof(struct htab_item));
    if (it.ptr == NULL) {
        fprintf(stderr, "Error: nepodarilo se vlozit klic do tabulky\n");
        return htab_end(t);
    }

    /* Alokace a kontrola alokace pameti pro novy zaznam */
    it.ptr->key = malloc(strlen(key) + 1);

    if (htab_iterator_get_key(it) == NULL) {
        free(it.ptr);
        return htab_end(t);
    }

    /* Inicializace nove polozky a uprava dat tabulky */
    strcpy(it.ptr->key, key);
    htab_iterator_set_value(it, 0);
    it.ptr->next = t->array[index];
    t->array[index] = it.ptr;
    t->size++;
    return it;
}
