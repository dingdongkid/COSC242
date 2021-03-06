#include <stdio.h>
#include <stdlib.h> 
#include <assert.h>
#include <ctype.h>
#include "mylib.h"

/**
 * Library class for 242 assignment.
 * @author Andrew Daw, Makoto McLennan, Nicholas Dong.
 */


/**
   Allocates memory of size s and returns address for allocated memory.
   @param s the size of memory to be allocated.
   @return result, a pointer to the memory allocated.
*/
void *emalloc(size_t s) {
    void *result = malloc(s);
    if(result == NULL){
        fprintf(stderr, "Memory allocation failed! \n");
        exit(EXIT_FAILURE);
    }
    return result;
}

/**
   Reads next word from a file stream and converts to an int.
   @param s the word to be converted to int.
   @param limit the size of the word to be converted
   @param stream the file stream in which the word is read from.
   @return the int representing the word 
*/
int getword(char *s, int limit, FILE *stream) {
    int c;
    char *w = s;
    assert(limit > 0 && s != NULL && stream != NULL);
    /* skip to the start of the word */
    while (!isalnum(c = getc(stream)) && EOF != c)
	;
    if (EOF == c) {
        return EOF;
    } else if (--limit > 0) { /* reduce limit by 1 to allow for the \0 */
        *w++ = tolower(c);
    }
    while (--limit > 0) {
        if (isalnum(c = getc(stream))) {
            *w++ = tolower(c);
        } else if ('\'' == c) {
            limit++;
        } else {
            break;
        }
    }
    *w = '\0';
    return w - s;
}



