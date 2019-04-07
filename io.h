/**
 *	@file	io.h
 *	@author	Simon Sedlacek, FIT
 *	@date	29.3.2019
 *	@note	Reseni: IJC-DU2, priklad 2)
 *	Prelozeno: gcc 8.3.1 - Fedora release 29 (Twenty Nine) x86_64 
 */

#ifndef __IO_H__
#define __IO_H__

#include <stdio.h>
#include <string.h>
#include <ctype.h>

/**
 * @brief Nacte ze souboru jedno slovo a ulozi ho do zadaneho retezce. Pokud
 * by delka slova mela presahnout zadane maximum, funkce zbytek slova preskoci
 *
 * @param s Retezec pro ulozeni slova
 * @param max Funkce nacita az max - 1 znaku, pricemz max je delka pole s.
 * @param f Soubor, ze ktereho bude slovo nacteno
 *
 * @return Pocet nactenych znaku (pripadne cislo vetsi nez max pri prilis
 * dlouhem slove), nebo EOF v pripade konce souboru
 */
int get_word(char *s, int max, FILE *f);

#endif
