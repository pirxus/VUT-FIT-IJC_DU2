/**
 *	@file	htab_init.c
 *	@author	Simon Sedlacek, FIT
 *	@date	5.4.2019
 *	@note	Reseni: IJC-DU2, priklad 2)
 *	Prelozeno: gcc 8.3.1 - Fedora release 29 (Twenty Nine) x86_64 
 */

#include <stdlib.h>
#include "htab.h"
#include "htab_private.h"

htab_t *htab_init(size_t n) {
    if (n == 0) {
        fprintf(stderr, "Error: tabulka musi mit alespon jeden radek\n");
        return NULL;
    }

    htab_t *new = malloc(sizeof(htab_t) + sizeof(struct htab_item *) * n);

    if (new == NULL) {
        fprintf(stderr, "Error: nepodarilo se alokovat pamet pro tabulku\n");
        return NULL;
    }

    new->size = 0;
    new->arr_size = n;

    for (size_t i = 0; i < n; i++) {
        new->array[i] = NULL;
    }

    return new;
}
