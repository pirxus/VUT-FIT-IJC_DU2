/**
 *	@file	wordcount.c
 *	@author	Simon Sedlacek, FIT
 *	@date	29.3.2019
 *	@note	Reseni: IJC-DU2, priklad 2)
 *	Prelozeno: gcc 8.3.1 - Fedora release 29 (Twenty Nine) x86_64 
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "io.h"
#include "htab.h"


#define WORD_LIMIT 128

int main(void) {

    char s[128] = {0};
    int count = 0;
    bool print_warning = true;

    while ((count = get_word(s, WORD_LIMIT, stdin)) != EOF) {

        if (count >= WORD_LIMIT && print_warning == true) {
            print_warning = false;
            fprintf(stderr, "Warning: Slovo prekrocilo limit delky slova, "
                    "dalsi slova jsou potencialne zkracena\n");
        }

        printf("%s\n", s);
    }
    return 0;
}
