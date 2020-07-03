#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mylib.h"
#include "htable.h"

struct htablerec {
    int capacity;
    int num_keys;
    char **keys;
    int *freqs;
    /*int *stats*/
    /*hashing_t method*/
};

/**
 * Converts a word into an integer.
 * @param *word a given word.
 * @return a converted, positive integer.
 */
static unsigned int htable_word_to_int(char *word) {
    unsigned int result = 0;
    while (*word != '\0') {
        result = (*word++ + 31 * result);
    }
    return result;
}

/**
 * Allocates a given amount of memory.
 * @param s size of section to be allocated.
 * @return allocated memory.
 */
void *emalloc(size_t s) {
    void *result = malloc(s);
    if(NULL == result) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    return result;
}

/**
 * Frees a hashtable and its contents.
 * @param h given htable.
 */
void htable_free(htable h) {
    int i;
    for(i = 0; i < h->capacity; i++) {
        free(h->keys[i]);
    }
    free(h->keys);
    free(h->freqs);
    free(h);
}

/**
 * Inserts a key into a hash table. Linear probing in case of collisions.
 * @param *str a string to be inserted.
 * @return number of times a key has been entered.
 */
int htable_insert(htable h, char *str) {
    int i;
    int collisions = 0;
    int index = (htable_word_to_int(str) % h->capacity);
    if(h->keys[index] == NULL) {
        h->keys[index] = emalloc((strlen(str)+1) * sizeof h->keys[index][0]);
        strcpy(h->keys[index], str);
        h->freqs[index]++;
        h->num_keys++;
        return 1;
    } else if(strcmp(h->keys[index], str) == 0) {
        h->freqs[index]++;
        return h->freqs[index];
    } else if(h->num_keys < h->capacity) {
        i = index++;
        collisions++;
        while(collisions <= h->capacity) {
            if(h->keys[i] == NULL) {
                h->keys[i] = emalloc((strlen(str)+1) * sizeof
                                     h->keys[index][0]);
                strcpy(h->keys[i], str);
                h->freqs[i]++;
                h->num_keys++;
                return 1;
            } else if(strcmp(h->keys[i], str) == 0) {
                h->freqs[i]++;
                return h->freqs[i];
            }
            i++;
            if(i == h->capacity) {
                i -= h->capacity;
            }
        }
    } else {
        return 0;
    }
    return 0;
}

/**
 * Creates a new hash table, setting capacity, and creating arrays for strings
 * and the frequency of their appearance.
 * @param capacity the size of the hash table.
 * @return a new hash table.
 */
htable htable_new(int capacity) {
    int i;
    htable result = emalloc(sizeof *result);
    result->capacity = capacity;
    result->num_keys = 0;
    result->freqs = emalloc(result->capacity * sizeof result->freqs[0]);
    result->keys = emalloc(result->capacity * sizeof result->keys[0]);    
    for(i = 0; i < result->capacity; i++) {
        result->freqs[i] = 0;
        result->keys[i] = NULL;
    }
    return result;
}

/**
 * Prints hash table.
 * @param h a hash table to read from.
 * @param *stream a file to print into.
 */
void htable_print(htable h, FILE *stream) {
    int i;
    for(i = 0; i < h->capacity; i++) {
        if(h->keys[i] != NULL) {
            fprintf(stream, "%s\n", h->keys[i]);
        }
    }
}

/**
 * Looks for a key in a hash table. Linear probing in case of collisions.
 * @param *str a string to be found.
 * @return frequency of key.
 */
int htable_search(htable h, char *str) {
    int collisions = 0;
    int index = (htable_word_to_int(str) % h->capacity);
    while(h->keys[index] != NULL && strcmp(h->keys[index], str) != 0 &&
          collisions < h->capacity) {
        index++;
        collisions++;
        if(index == h->capacity) {
            index = 0;
        }
    }
    if(collisions == h->capacity) {
        return 0;
    } else {
        return h->freqs[index];
    }
    return 0;
}

int main(void) {
    htable h = htable_new(18143);
    char word[256];
    
    while (getword(word, sizeof word, stdin) != EOF) {
        htable_insert(h, word);
    }
    
    htable_print(h, stdout);
    printf("%d\n", htable_search(h, "the"));
    htable_free(h);
    
    return EXIT_SUCCESS;
}

/*
int main(void) {
    htable h = htable_new(113);
    char word[256];
    char op;
     We must have a space before the %c 
    while (2 == scanf(" %c %255s", &op, word)) {
        if ('+' == op) {
            htable_insert(h, word);
        } else if ('?' == op) {
            printf("%d %s\n", htable_search(h, word), word);
        }
    }
    htable_free(h);
    return EXIT_SUCCESS;
}
*/
