#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_MAX 30000

void insertion_sort(int *a, int n) {
    int p, key, index;

    /* For all positions except the first */
    for(p = 0; p < n; p++) {
        /* Pull out item p and store it */
        key = a[p];

        /* Move each item left of p, and greater than key, one to the right */
        index = p-1;
        while (index >= 0 && a[index] > key) {
            a[index+1] = a[index];
            index--;
        }

        /* Place key in the leftmost vacated position */
        a[index+1] = key;
        /* sorting code*/
    }
}

void print_array(int *a, int n) {
    if (n > 0) {
        printf("%d\n", a[0]);
        print_array(a+1, n-1);
    }
}

void int_search(int *a, int count, int b) {
    int i;
    for(i = 0; i < count; i++) {
        if(a[i] == b) {
            printf("+\n");
            return;
        }
    }
    printf("-\n");
}

int main(int argc, char **argv) {
    FILE *infile;
    int my_array[ARRAY_MAX];
    int compare[ARRAY_MAX];
    clock_t start, end;
    int count;
    int count2;

    if (NULL == (infile = fopen(argv[1], "r"))) {
        fprintf(stderr, "%s: can't find file %s\n", argv[0], argv[1]);
        return EXIT_FAILURE;
    }

    count = 0;
    while (count < ARRAY_MAX && 1 == fscanf(infile, "%d", &my_array[count])) {
        count++;
    }
    
    start = clock();
    insertion_sort(my_array, count);
    end = clock();

    count2 = 0;
    while (count2 < ARRAY_MAX && 1 == fscanf(stdin, "%d", &compare[count2])) {
        int_search(my_array, count, compare[count2]);
        count2++;
    }
        
    
    fclose(infile);
 
    /* print_array(my_array, count);*/
    
    fprintf(stderr, "%d %f\n", count, (end-start) / (double)CLOCKS_PER_SEC);
    return EXIT_SUCCESS;
}
