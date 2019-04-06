/**
 *	@file	htab_iterator_get.c
 *	@author	Simon Sedlacek, FIT
 *	@date	5.4.2019
 *	@note	Reseni: IJC-DU2, priklad 2)
 *	Prelozeno: gcc 8.3.1 - Fedora release 29 (Twenty Nine) x86_64 
 */

#include <stdlib.h>
#include "htab.h"
#include "htab_private.h"

extern bool htab_iterator_valid(htab_iterator_t it);

extern bool htab_iterator_equal(htab_iterator_t it1, htab_iterator_t it2);

const char *htab_iterator_get_key(htab_iterator_t it) {
    if (it.ptr == NULL)
        return NULL;
    return it.ptr->key;
}

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

htab_iterator_t htab_lookup_add(htab_t *t, const char *key) {
    int index = (htab_hash_function(key) % t->arr_size);
    htab_iterator_t it = {.ptr = t->array[index], .t = t, .idx = index};

    /* Projdeme cely seznam na danem indexu a zjistime, zda se v tabulce jiz
     * dane slovo nachazi */
    while (htab_iterator_valid(it)) {
        if (!strcmp(htab_iterator_get_key(it), key)) {
            it.ptr->data++;
            return it;
        }
        htab_iterator_next(it);
    }

    /* Tabulka danou polozku neobsahovala, tudiz musime polozku pridat */
    it.ptr = malloc(sizeof(struct htab_item));
    if (it.ptr == NULL)
        return htab_end(t);
    it.ptr->key = malloc(strlen(key) + 1);
    if (htab_iterator_get_key(it) == NULL) {
        free(it.ptr);
        return htab_end(t);
    }

    strcpy(it.ptr->key, key);
    htab_iterator_set_value(it, 1);
    it.ptr->next = t->array[index];
    t->array[index] = it.ptr;
    t->size++;
    return it;
}

htab_iterator_t htab_begin(const htab_t *t) {
    htab_iterator_t begin;

    begin.ptr = t->array[0];
    begin.t = t;
    begin.idx = 0;

    return begin;
}

htab_iterator_t htab_end(const htab_t *t) {
    htab_iterator_t end;

    end.ptr = NULL;
    end.t = t;
    end.idx = t->arr_size - 1;

    return end;
}

htab_iterator_t htab_iterator_next(htab_iterator_t it) {
    if (!htab_iterator_valid(it)) {
        if ((size_t)it.idx == htab_bucket_count(it.t) - 1)
            return it;

        it.idx++;
        it.ptr = it.t->array[it.idx];
        return it;

    } else {
        it.ptr = it.ptr->next;
        return it;
    }
}
