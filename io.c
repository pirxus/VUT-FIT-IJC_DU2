/**
 *	@file	io.c
 *	@author	Simon Sedlacek, FIT
 *	@date	29.3.2019
 *	@note	Reseni: IJC-DU2, priklad 2)
 *	Prelozeno: gcc 8.3.1 - Fedora release 29 (Twenty Nine) x86_64 
 */

#include "io.h"

int get_word(char *s, int max, FILE *f) {
    if (f == NULL || s == NULL)
        return EOF;

    int c;
    int i = 0;

    /* Preskocime bile znaky */
    while ((c = fgetc(f))) {
        if (c == EOF)
            return EOF;
        if (!isspace(c))
            break;
    }
    
    /* Nacteme slovo */
    while (i < max) {
        s[i] = c;
        i++;
        c = fgetc(f);
        if (isspace(c) || c == EOF)
            break;
    }

    /* Zakoncime retezec */
    s[i] = '\0';

    /* Preskocime zbytek dlouheho slova */
    int overflow = 0;
    if (i == max) {
        overflow = -1;
        do {
            c = fgetc(f);
            overflow++;
        } while (!isspace(c) && c != EOF);
    }

    return i + overflow;
}
