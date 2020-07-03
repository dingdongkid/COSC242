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
    int *stats;
    hashing_t method;
};

/**
 * Prints out a line of data from the hash table to reflect the state
 * the table was in when it was a certain percentage full.
 * Note: If the hashtable is less full than percent_full then no data
 * will be printed.
 *
 * @param h - the hash table.
 * @param stream - a stream to print the data to.
 * @param percent_full - the point at which to show the data from.
 */
static void print_stats_line(htable h, FILE *stream, int percent_full) {
    int current_entries = h->capacity * percent_full / 100;
    double average_collisions = 0.0;
    int at_home = 0;
    int max_collisions = 0;
    int i = 0;

    if (current_entries > 0 && current_entries <= h->num_keys) {
        for (i = 0; i < current_entries; i++) {
            if (h->stats[i] == 0) {
                at_home++;
            } 
            if (h->stats[i] > max_collisions) {
                max_collisions = h->stats[i];
            }
            average_collisions += h->stats[i];
        }
    
        fprintf(stream, "%4d %10d %10.1f %10.2f %11d\n", percent_full, 
                current_entries, at_home * 100.0 / current_entries,
                average_collisions / current_entries, max_collisions);
    }
}

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
 * Resolves collisions via double hashing step.
 * @param h htable to insert into.
 * @param i_key index of key to be changed.
 * @return new index to insert into.
 */
static unsigned int htable_step(htable h, int i_key) {
    return 1 + (i_key % (h->capacity - 1));
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
    free(h->stats);
    free(h);
}

/**
 * Inserts a key into a hash table. Resolves collisions.
 * @param *str a string to be inserted.
 * @return number of times a key has been entered.
 */
int htable_insert(htable h, char *str) {
    int collisions = 0;
    int index = (htable_word_to_int(str) % h->capacity);
    while(collisions <= h->capacity) {
        if(h->keys[index] == NULL) {
            h->keys[index] = emalloc((strlen(str)+5) * sizeof str[0]);
            strcpy(h->keys[index], str);
            h->stats[h->num_keys] = collisions;
            h->freqs[index]++;
            h->num_keys++;
            return 1;
        } else if(strcmp(h->keys[index], str) == 0) {
            h->freqs[index]++;
            return h->freqs[index];
        } else {
            if(h->method == LINEAR_P) {
                index++;
            }
            if(h->method == DOUBLE_H) {
                index = htable_step(h, index);
            }
            if(index >= h->capacity) {
                index -= h->capacity;
            }
            collisions++;
        }
    }
    return 0;
}

/**
 * Creates a new hash table, setting capacity, and creating arrays for strings
 * and the frequency of their appearance.
 * @param capacity the size of the hash table.
 * @return a new hash table.
 */
htable htable_new(int capacity, hashing_t method) {
    int i;
    htable result = emalloc(sizeof(*result));
    result->method = method;
    result->capacity = capacity;
    result->num_keys = 0;
    result->freqs = emalloc(result->capacity * sizeof result->freqs[0]);
    result->keys = emalloc(result->capacity * sizeof result->keys[0]);
    result->stats = emalloc(result->capacity * sizeof result->stats[0]);
    for(i = 0; i < capacity; i++) {
        result->freqs[i] = 0;
        result->stats[i] = 0;
        result->keys[i] = NULL;
    }
    return result;
}

/**
 * Prints hash table.
 * @param h a hash table to read from.
 * @param *stream a file to print into.
 */
void htable_print_entire_table(htable h, FILE *stream) {
    int i;
    for(i = 0; i < h->capacity; i++) {
        if(h->keys[i] != NULL) {
            fprintf(stream, "%5d %5d %5d   %s\n", i, h->freqs[i], h->stats[i],
                    h->keys[i]);
        }
    }
}

void htable_print(htable h, void f(int freq, char *word)) {
    int i;
    for(i = 0; i < h->capacity; i++) {
        if(h->keys[i] != NULL) {
            f(h->freqs[i], h->keys[i]);
        }
    }
}

/**
 * Prints out a table showing what the following attributes were like
 * at regular intervals (as determined by num_stats) while the
 * hashtable was being built.
 *
 * @li Percent At Home - how many keys were placed without a collision
 * occurring.
 * @li Average Collisions - how many collisions have occurred on
 *  average while placing all of the keys so far.
 * @li Maximum Collisions - the most collisions that have occurred
 * while placing a key.
 *
 * @param h the hashtable to print statistics summary from.
 * @param stream the stream to send output to.
 * @param num_stats the maximum number of statistical snapshots to print.
 */
void htable_print_stats(htable h, FILE *stream, int num_stats) {
    int i;

    fprintf(stream, "\n%s\n\n", 
            h->method == LINEAR_P ? "Linear Probing" : "Double Hashing"); 
    fprintf(stream, "Percent   Current   Percent    Average      Maximum\n");
    fprintf(stream, " Full     Entries   At Home   Collisions   Collisions\n");
    fprintf(stream, "-----------------------------------------------------\n");
    for (i = 1; i <= num_stats; i++) {
        print_stats_line(h, stream, 100 * i / num_stats);
    }
    fprintf(stream, "-----------------------------------------------------\n\n");
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
          collisions <= h->capacity) {
        if(h->method == LINEAR_P) {
            index++;
        }
        if(h->method == DOUBLE_H) {
            index = htable_step(h, index);
        }
        collisions++;
        if(index == h->capacity) {
            index -= h->capacity;
        }
    }
    if(collisions == h->capacity) {
        return 0;
    } else {
        return h->freqs[index];
    }
    return 0;
}
