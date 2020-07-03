#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_MAX 30000

void merge(int *array, int *workspace, int n) {
    int i, j, k;
    i = 0;
    j = n/2;
    k = 0;

    while (i < n/2 && j < n) {
        if (array[i] < array[j]) {
            workspace[k++] = array[i++];
        } else {
            workspace[k++] = array[j++];
        }
    }

    while (i < n/2) {
        workspace[k++] = array[i++];
    }

    while (j < n) {
        workspace[k++] = array[j++];
    }
    return;
}

void merge_sort(int *a, int *w, int n) {
    int i;
    if(n > 1) {
        merge_sort(a, w, n/2);
        merge_sort(a + (n/2), w, (n - n/2));
        merge(a, w, n);

        for (i = 0; i < n; i++) {
            a[i] = w[i];
        }
    }        
    return;
}


void print_array(int *a, int n) {
    if (n > 0) {
        printf("%d\n", a[0]);
        print_array(a+1, n-1);
    }
}

int main(void) {
    int my_array[ARRAY_MAX];
    int workspace[ARRAY_MAX];
    clock_t start, end;
    int i, count = 0;

    while (count < ARRAY_MAX && 1 == scanf("%d", &my_array[count])) {
        count++;
    }
    start = clock();
    merge_sort(my_array, workspace, count);
    end = clock();
    
    for(i = 0; i < count; i++) {
        printf("%d\n", my_array[i]);
    }
    
    fprintf(stderr, "%d %f\n", count, (end-start) / (double)CLOCKS_PER_SEC);
    return EXIT_SUCCESS;
}
