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

int main(void) {
    int my_array[ARRAY_MAX];
    clock_t start, end;
    int i, count = 0;

    while (count < ARRAY_MAX && 1 == scanf("%d", &my_array[count])) {
        count++;
    }
    start = clock();
    insertion_sort(my_array, count);
    end = clock();
    
    for(i = 0; i < count; i++) {
        printf("%d\n", my_array[i]);
    }
    fprintf(stderr, "%d %f\n", count, (end-start) / (double)CLOCKS_PER_SEC);
    return EXIT_SUCCESS;
}
