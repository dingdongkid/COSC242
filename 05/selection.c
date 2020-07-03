#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define STRING_LEN 80
#define ARRAY_LEN 10001

void selection_sort(char **a, int n) {
    int p;
    char value[STRING_LEN];
    char *temp;
    int i, low;
    
    /* For all positions except the last */
    for(p = 0; p < n-1; p++) {
        
        /* Find the smallest item from p to (n-1) */
        low = p;
        value[strlen(a[p])+1] = malloc((strlen(a[p])+1)* sizeof value[0]);
        strcpy(value,a[p]);
        for(i = p; i < n; i++) {
            if(strcmp(a[i], value) < 0) {
                low = i;
                strcpy(value, a[i]);
            }
        }

        /* Swap the item you find with whatever is at p */
        temp = a[p];
        a[p] = a[low];
        a[low] = temp;
        /* sorting code*/
    }
}

void *emalloc(size_t s) {
    void *result = malloc(s);
    if(NULL == result) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    return result;
}

int main(void) {
    char word[STRING_LEN];
    char *my_array[ARRAY_LEN];
    /*   clock_t start, end;*/
    int i, count = 0;

    while (count < ARRAY_LEN && 1 == scanf("%79s", word)) {
        my_array[count] = emalloc((strlen(word) + 1) * sizeof word[0]);
        strcpy(my_array[count++], word);
        count++;
    }

    start = clock();
    selection_sort(my_array, count);
    end = clock(); 
    
    for(i = 0; i < count; i++) {
        printf("%s\n", my_array[i]);
    }

    fprintf(stderr, "%d %f\n", count, (end-start) / (double)CLOCKS_PER_SEC);
    
    for(i = 0; i < count; i++) {
        free(my_array[i]);
    }
    return EXIT_SUCCESS;
}
