/**
 *	@file	htab_iterator_end.c
 *	@author	Simon Sedlacek, FIT
 *	@date	14.4.2019
 *	@note	Reseni: IJC-DU2, priklad 2)
 *	Prelozeno: gcc 8.3.1 - Fedora release 29 (Twenty Nine) x86_64 
 */

#include <stdlib.h>
#include "htab.h"
#include "htab_private.h"

htab_iterator_t htab_end(const htab_t *t) {
    htab_iterator_t end;

    end.ptr = NULL;

    if (t == NULL) {
        end.t = NULL;
        end.idx = 0;
    } else {
        end.t = t;
        end.idx = t->arr_size - 1;
    }

    return end;
}
