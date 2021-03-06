/**
 * Header file for mylib.c
 * @author Andrew Daw, Makoto McLennan, Nicholas Dong.
 */

#ifndef MYLIB_H_
#define MYLIB_H_

#include <stdio.h>

extern void *emalloc(size_t);
extern int getword(char *s, int limit, FILE *stream);

#endif
