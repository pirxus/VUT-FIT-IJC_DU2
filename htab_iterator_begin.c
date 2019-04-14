/**
 *	@file	htab_iterator_begin.c
 *	@author	Simon Sedlacek, FIT
 *	@date	14.4.2019
 *	@note	Reseni: IJC-DU2, priklad 2)
 *	Prelozeno: gcc 8.3.1 - Fedora release 29 (Twenty Nine) x86_64 
 */

#include <stdlib.h>
#include "htab.h"
#include "htab_private.h"

htab_iterator_t htab_begin(const htab_t *t) {
    htab_iterator_t begin;
    begin.ptr = NULL;
    begin.t = NULL;
    begin.idx = 0;

    if (t == NULL)
        return begin;

    begin.t = t;

    /* Najdeme prvni validni zaznam v tabulce */
    for (size_t i = 0; i < t->arr_size; i++) {
        if ((begin.ptr = t->array[i]) != NULL) {
            begin.idx = i;
            break;
        }
    }

    return begin;
}
