/**
 *	@file	htab_move.c
 *	@author	Simon Sedlacek, FIT
 *	@date	5.4.2019
 *	@note	Reseni: IJC-DU2, priklad 2)
 *	Prelozeno: gcc 8.3.1 - Fedora release 29 (Twenty Nine) x86_64 
 */

#include "htab.h"
#include "htab_private.h"

htab_t *htab_move(size_t n, htab_t *from) {
    if (from == NULL)
        return NULL;

    htab_t *new = htab_init(n);

    if (new == NULL)
        return NULL;

    new->size = from->size;

    /* Zkopirujeme seznamy do nove tabulky */
    for (size_t i = 0; i < from->size; i++) {
        new->array[i] = from->array[i];
        from->array[i] = NULL;
    }

    from->size = 0;
    return new;
}
