#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_MAX 30000

void selection_sort(int *a, int n) {
    int p, value, i, low;
    
    /* For all positions except the last */
    for(p = 0; p < n-1; p++) {
        
        /* Find the smallest item from p to (n-1) */
        low = p;
        value = a[p];
        for(i = p; i < n; i++) {
            if(a[i] < value) {
                low = i;
                value = a[i];
            }
        }

        /* Swap the item you find with whatever is at p */
        int temp = a[p];
        a[p] = a[low];
        a[low] = temp;
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
    selection_sort(my_array, count);
    end = clock();
    
    for(i = 0; i < count; i++) {
        printf("%d\n", my_array[i]);
    }
    fprintf(stderr, "%d %f\n", count, (end-start) / (double)CLOCKS_PER_SEC);
    return EXIT_SUCCESS;
}
