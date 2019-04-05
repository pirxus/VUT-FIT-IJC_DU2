/**
 *	@file	htab_hash.c
 *	@author	Simon Sedlacek, FIT
 *	@date	5.4.2019
 *	@note	Reseni: IJC-DU2, priklad 2)
 *	Prelozeno: gcc 8.3.1 - Fedora release 29 (Twenty Nine) x86_64 
 */

#include "htab.h"

unsigned int htab_hash_function(const char *str) {
    uint32_t h = 0;
    const unsigned char *p;
    for(p = (const unsigned char*)str; *p != '\0'; p++)
        h = (65599 * h) + *p;
    return h;
}
