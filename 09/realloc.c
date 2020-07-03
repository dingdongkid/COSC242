#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"

static void array_print(int *a, int n) {
    int i;

    for (i = 0; i < n; i++) {
        printf("%d\n", a[i]);
    }
}

void insertion_sort(int *a, int n) {
    int p, key, index;

    /* For all positions except the first */
    for(p = 1; p < n; p++) {
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
    int capacity = 2;
    int itemcount = 0;
    int item;
    int *my_array = emalloc(capacity * sizeof my_array[0]);

    while ( 1 == scanf("%d", &item)) {
        if (itemcount == capacity) {
            capacity += capacity;
            my_array = erealloc(my_array, capacity * sizeof my_array[0]);
        }
        my_array[itemcount++] = item;
    }

    insertion_sort(my_array, itemcount);

    array_print(my_array, itemcount);
    free(my_array);

    return EXIT_SUCCESS;
}
                
