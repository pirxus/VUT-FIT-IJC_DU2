/**
 *	@file	htab_move.c
 *	@author	Simon Sedlacek, FIT
 *	@date	5.4.2019
 *	@note	Reseni: IJC-DU2, priklad 2)
 *	Prelozeno: gcc 8.3.1 - Fedora release 29 (Twenty Nine) x86_64 
 */

#include "htab.h"
#include "htab_private.h"

htab_t *htab_move(size_t n, htab_t *from) {
    if (from == NULL || n == 0)
        return NULL;

    htab_t *new = htab_init(n);

    if (new == NULL) {
        fprintf(stderr, "Error: nepodarilo se alokovat pamet "
                "pro novou tabulku\n");
        return NULL;
    }

    /* Pomocne iteratory pro prochazeni puvodni tabulkou a
     * kontrolu operace vlozeni zaznamu do nove tabulky */
    htab_iterator_t iterator, check;

    /* Vsechny polozky z puvodni tabulky postupne vlozime do nove tabulky */
    for (iterator = htab_begin(from);
            htab_iterator_valid(iterator);
            iterator = htab_iterator_next(iterator)) {

        check = htab_lookup_add(new, iterator.ptr->key);
        
        if (!htab_iterator_valid(check)) {
            fprintf(stderr, "Error: nepodarilo se presunout polozku "
                    "do nove tabulky\n");
            htab_clear(new);
            return NULL;
        }

        htab_iterator_set_value(check, htab_iterator_get_value(iterator));
        new->size++;
    }

    htab_clear(from);
    return new;
}
