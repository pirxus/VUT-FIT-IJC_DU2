/**
 *	@file	htab_iterator_get_key.c
 *	@author	Simon Sedlacek, FIT
 *	@date	14.4.2019
 *	@note	Reseni: IJC-DU2, priklad 2)
 *	Prelozeno: gcc 8.3.1 - Fedora release 29 (Twenty Nine) x86_64 
 */

#include <stdlib.h>
#include <assert.h>
#include "htab.h"
#include "htab_private.h"

const char *htab_iterator_get_key(htab_iterator_t it) {
    assert(it.ptr != NULL);
    return it.ptr->key;
}
