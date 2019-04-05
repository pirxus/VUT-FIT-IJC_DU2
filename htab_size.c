/**
 *	@file	htab_size.c
 *	@author	Simon Sedlacek, FIT
 *	@date	5.4.2019
 *	@note	Reseni: IJC-DU2, priklad 2)
 *	Prelozeno: gcc 8.3.1 - Fedora release 29 (Twenty Nine) x86_64 
 */

#include "htab.h"
#include "htab_private.h"

size_t htab_size(const htab_t *t) {
    if (t == NULL)
        return 0;
    return t->size;
}
