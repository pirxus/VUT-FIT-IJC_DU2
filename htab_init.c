/**
 *	@file	htab_init.c
 *	@author	Simon Sedlacek, FIT
 *	@date	5.4.2019
 *	@note	Reseni: IJC-DU2, priklad 2)
 *	Prelozeno: gcc 8.3.1 - Fedora release 29 (Twenty Nine) x86_64 
 */

#include "htab.h"
#include "htab_private.h"

htab_t *htab_init(size_t n) {
    htab_t *new = malloc(sizeof(htab_t) + sizeof(struct htab_item*) * n);

    if (new == NULL)
        return NULL;

    new->size = 0;
    new->arr_size = n;

    return new;
}
