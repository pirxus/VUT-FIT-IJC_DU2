/**
 *	@file	htab_private.h
 *	@author	Simon Sedlacek, FIT
 *	@date	5.4.2019
 *	@note	Reseni: IJC-DU2, priklad 2)
 *	Prelozeno: gcc 8.3.1 - Fedora release 29 (Twenty Nine) x86_64 
 */

#ifndef __HTABLE_PRIVATE_H__
#define __HTABLE_PRIVATE_H__

#include "htab.h"

/**
 * @brief
 */
struct htab {
    size_t size;
    size_t arr_size;
    struct htab_item *array[];
};

/**
 * @brief
 */
struct htab_item {
    char *key;
    size_t data;
    struct htab_item *next;
};

#endif
