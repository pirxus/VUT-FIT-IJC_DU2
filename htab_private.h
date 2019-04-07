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
 * @struct htab
 * @brief Struktura hashovaci tabulky.
 *
 * @var size
 * Aktualni pocet zaznamu v tabulce.
 * @var arr_size
 * Pocet radku tabulky.
 * @var array
 * Pole seznamu se zaznamy.
 */
struct htab {
    size_t size;
    size_t arr_size;
    struct htab_item *array[];
};

/**
 * @struct htab_item
 * @brief Struktura zaznamu v hashovaci tabulce
 *
 * @var key
 * Klic daneho zaznamu.
 * @var data
 * Pocet zaznamu vazajicich se k danemu klici.
 * @var next
 * Ukazatel na dalsi polozku seznamu.
 */
struct htab_item {
    char *key;
    int data;
    struct htab_item *next;
};

#endif
