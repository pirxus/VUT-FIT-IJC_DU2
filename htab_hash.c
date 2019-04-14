/**
 *	@file	htab_hash.c
 *	@author	Simon Sedlacek, FIT
 *	@date	5.4.2019
 *	@note	Reseni: IJC-DU2, priklad 2)
 *	Prelozeno: gcc 8.3.1 - Fedora release 29 (Twenty Nine) x86_64 
 */

#include <stdint.h>
#include "htab.h"

#ifndef HASHTEST

unsigned int htab_hash_function(const char *str) {
    uint32_t h = 0;
    const unsigned char *p;

    for (p = (const unsigned char*)str; *p != '\0'; p++)
        h = (65599 * h) + *p;

    return h;
}

#else

/* Nahradni hash funkce */
unsigned int htab_hash_function(const char *str) {
    uint32_t hash, i;

    for (hash = i = 0; str[i]; ++i) {
        hash += str[i];
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }

    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    return hash;
}

#endif
