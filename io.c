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

    /* Preskocime pripadne whitespace characters */
    do {
        c = fgetc(f);
        if (c == EOF)
            return EOF;
    } while(isspace(c));

    /* Nacteme jedno slovo a zakoncime nulovym bytem */
    do {
        s[i++] = c;
        c = fgetc(f);
        if (isspace(c) || c == EOF) {
            s[i] = '\0';
            return i;
        }

    } while (i < max - 1);

    s[i] = '\0';

    /* Preskocime zbytek slova */
    int overflow = 0;
    while(!isspace(c = fgetc(f))) {
        if (c == EOF)
            return i;
        overflow = 1;
    }
    
    return i + overflow;
}
