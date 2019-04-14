/**
 *	@file	htab_iterator_value.c
 *	@author	Simon Sedlacek, FIT
 *	@date	14.4.2019
 *	@note	Reseni: IJC-DU2, priklad 2)
 *	Prelozeno: gcc 8.3.1 - Fedora release 29 (Twenty Nine) x86_64 
 */

#include <stdlib.h>
#include "htab.h"
#include "htab_private.h"

int htab_iterator_get_value(htab_iterator_t it) {
    if (it.ptr == NULL)
        return 0;
    return it.ptr->data;
}

int htab_iterator_set_value(htab_iterator_t it, int val) {
    if (it.ptr == NULL)
        return -1;
    it.ptr->data = val;
    return 0;
}
