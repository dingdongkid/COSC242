#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "htable.h"
#include "mylib.h"
#include "tree.h"

#define DICT_LEN 113
#define STRING_LEN 80

/**
 * Prints each nodes' frequency and word.
 * @param freq frequency of word.
 * @param *word string of node.
 */
static void print_info(int freq, char *word) {
    printf("%-4d %s\n", freq, word);
}

/**
 * Default help description.
 */
void help(){    
    printf("Usage: ./asgn [OPTION]... <STDIN>\n\n");
    printf("-T     Use a tree data structure (the default is a hash table)\n");
    printf("-c FILENAME  Check the spelling of words in FILENAME using words\n");
    printf("       read from stdin as the dictionary. Print all unknown\n");
    printf("       words to stdout. Print timing information and unknown\n");
    printf("       word count to stderr. When this option is given the -p\n");
    printf("       or -o options should be ignored.\n");
    printf("-d     Use double hashing as the collision resolution strategy)\n");
    printf("       (linear probing is the default)\n");
    printf("-e     Display entire contents of hash table on stderr\n");
    printf("-o     Output a representation of the tree in 'dot' form to the\n");
    printf("       file 'tree-view.dot' using the functions given in\n");
    printf("       output-dot.txt\n");
    printf("-p     Print stats info using the functions provided in\n");
    printf("       print-stats.txt instead of printing frequencies and words\n");
    printf("-r     Make the tree an rbt instead of the default bst.\n");
    printf("-s SNAPSHOTS Display up to the given number of stats snapshots\n");
    printf("       when given -p as an argument.\n");
    printf("-t TABLESIZE Use the first prime >= TABLESIZE as the size of\n");
    printf("       your hash table.\n");
    printf("-h     Print a help message describing how to use the program.\n");
    exit(EXIT_SUCCESS);
}

/**
 * Finds the next prime number.
 * @param hash table size.
 * @return next found prime.
 */
int next_prime(int i) {
    int j = 2;
    while(i > 0) {
        while(j < sqrt(i)) {
            if(i % j == 0) {
                i++;
                j = 2;
            } else {
                j++;
            }
        }
        return i;
    }
    return 0;
}


/**
 *Main method
 *@param argv. Program input e.g. flags
 *@return. Describes exit status
 */
int main(int argc, char *argv[]){
    const char *optstring = "Tc:deoprs:t:h";
    char option;

    int is_table = 0;
    int snapshots;

    tree_t tree_type = BST;
    tree t;
    hashing_t method = LINEAR_P;
    htable h;
    
    char word[STRING_LEN];
    int capacity = DICT_LEN;

    int c = 0;
    int unknown = 0;
    char *document = NULL;
    FILE *infile;

    int o = 0;
    int p = 0;
    int s = 0;
    int e = 0;
    
    double fill = 0, search = 0;
    clock_t start, end;
	
    while ((option = getopt(argc, argv, optstring)) != EOF) {
        switch (option) {
            
                 /* set data structure to table*/
            case 'T':
                is_table = 1;
                break;

                /*spellcheck*/
            case 'c':
                c = 1;
                document = optarg;
                break;
			
            case 'd':
                /*set collision resolution method to double hashing*/
                method = DOUBLE_H;
                break;
			
            case 'e':
                /*display hash table contents on stderr*/
                e = 1;
                break;
			
            case 'o':
                /*display tree as a dot function*/
                o = 1;
                break;
			
            case 'p':
                /*print stat information instead of frequencies and words*/
                p = 1;
                break;
			
            case 'r':
                if(is_table == 1) {
                    /*sets tree type to RBT*/
                    tree_type = RBT;
                }
                break;
			
            case 's':
                /*snapshots*/
                s = 1;
                snapshots = atoi(optarg);
                break;
			
            case 't':
                /*sets size of hashtable*/
                capacity = next_prime(atoi(optarg));
                break;
			
            case 'h':
                /*prints usage information*/
                help();
                return EXIT_SUCCESS;
		
            default :
                /* if an unknown option is given */
                help();
                exit(EXIT_FAILURE);
        }
    }
    /**Main execution starts here**/
    if(is_table == 0){
        start = clock();
        h = htable_new(capacity, method);
        while (getword(word, sizeof word, stdin) != EOF) {
            htable_insert(h, word);
        }
        end = clock();
        fill = (end - start)/(double)CLOCKS_PER_SEC;
    } else {
        t = tree_new(tree_type);    
        while (getword(word, sizeof word, stdin) != EOF) {
            t = tree_insert(t, word);
            t = set_black(t);
        }
    }

    if(e == 1) {
        if (is_table == 0){
            htable_print_entire_table(h, stderr);
            htable_print_entire_table(h, stdout);
        }
        htable_free(h);
        return EXIT_SUCCESS;
    }
    
    if(c == 1) {
        if(is_table == 0) {
            if(NULL == (infile = fopen(document, "r"))) {
                fprintf(stderr, "Can't open file using mode r.\n");
                htable_free(h);
                exit(EXIT_FAILURE);
            }
            start = clock();
            while(getword(word, sizeof word, infile) != EOF) {
                if(htable_search(h, word) == 0) {
                    printf("%s\n", word);
                    unknown++;
                }
            }
            end = clock();
            search = (end-start)/(double)CLOCKS_PER_SEC;
            htable_free(h);
        } else {
            if(NULL == (infile = fopen(document, "r"))) {
                fprintf(stderr, "Can't open file using mode r.\n");
                tree_free(t);
                exit(EXIT_FAILURE);
            }
            start = clock();
            while(getword(word, sizeof word, infile) != EOF) {
                if(tree_search(t, word) == 0) {
                    printf("%s\n", word);
                    unknown++;
                }
            }
            end = clock();
            search = (end-start)/(double)CLOCKS_PER_SEC;
            tree_free(t);
        }
        fprintf(stderr, "%14s%s%1.6f\n","Fill time",":", fill);
        fprintf(stderr, "%14s%s%1.6f\n","Search time",":", search);
        fprintf(stderr, "%14s%s%d\n","Unknown words","=", unknown);
        return EXIT_SUCCESS;
    }
    
    if (o == 1 && c == 0) {
        if(is_table == 1) {
            if (NULL == (infile = fopen("./tree-view.dot", "w"))) {
                fprintf(stderr, "Can't open file using mode w.\n");
                tree_free(t);
                exit(EXIT_FAILURE);
            }
            tree_output_dot(t, infile);
            fclose(infile);
            tree_free(t);
        }
        return EXIT_SUCCESS;
    }
    
    if(is_table == 0) {
        if (p == 1 && c == 0) {
            if(s == 1) {
                htable_print_stats(h, stderr, snapshots);
            } else {
                htable_print_stats(h, stderr, capacity);
            }
            htable_free(h);
            return EXIT_SUCCESS;
        }
    }
    
    if(is_table == 0) {
        htable_print(h, print_info);
        htable_free(h);
    } else {
        tree_preorder(t, print_info);
        tree_free(t);
    }
    return EXIT_SUCCESS;
}
