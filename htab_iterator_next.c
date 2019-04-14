/**
 *	@file	htab_iterator_next.c
 *	@author	Simon Sedlacek, FIT
 *	@date	14.4.2019
 *	@note	Reseni: IJC-DU2, priklad 2)
 *	Prelozeno: gcc 8.3.1 - Fedora release 29 (Twenty Nine) x86_64 
 */

#include <stdlib.h>
#include "htab.h"
#include "htab_private.h"

htab_iterator_t htab_iterator_next(htab_iterator_t it) {
    if (!htab_iterator_valid(it))
        return it;

    /* V pripade, ze aktualni zaznam je v seznamu posledni */
    if (it.ptr->next == NULL) {

        /* Pokud se zaznam nenachazi na poslednim radku tabulky,... */
        if ((size_t)it.idx < it.t->arr_size - 1)

            /* ...najdeme nejblizsi dalsi validni zaznam v tabulce */
            for (size_t i = it.idx + 1; i < it.t->arr_size; i++) {
                if ((it.ptr = it.t->array[i]) != NULL) {
                    it.idx = i;
                    return it;
                }
            }

        it = htab_end(it.t);

    } else {
        it.ptr = it.ptr->next;
    }
    
    return it;
}
