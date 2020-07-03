#include <stdio.h>
#include <stdlib.h>
#include "flexarray.h"

struct flexarrayrec {
    int capacity;
    int itemcount;
    int *items;
};

void *emalloc(size_t s) {
    void *result = malloc(s);
    if(NULL == result) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    return result;
}

void *erealloc(void *p, size_t s) {
    void *result = realloc(p, s);
    if (NULL == result) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    return result;
}

flexarray flexarray_new() {
    flexarray result = emalloc(sizeof *result);
    result->capacity = 2;
    result->itemcount = 0;
    result->items = emalloc(result->capacity * sizeof result->items[0]);
    return result;
}

void flexarray_append(flexarray f, int num) {
    if (f->itemcount == f->capacity) {
        f->capacity += f->capacity;
        f->items = erealloc(f->items, f->capacity * sizeof f->items[0]);
    }
    f->items[f->itemcount++] = num;
}

void flexarray_print(flexarray f) {
    int i;
    for (i = 0; i < f->itemcount; i++) {
        printf("%d\n", f->items[i]);
    }
}

static void quick_sort(int *a, int n) {
    int pivot, i, j, temp;
    if (n > 1) {
        pivot = a[0];
        i = -1;
        j = n+1;
        for(;;) {
            do {
                i++;
            } while (a[i] < pivot);
            do {
                j--;
            } while (a[j] > pivot);
            if (i < j) {
                temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            } else {
                break;
            }
        }
        quick_sort(a, j + 1);
        quick_sort(a + j + 1, n - j - 1);
    }
}

void flexarray_sort(flexarray f) {
    quick_sort(f->items,  f->itemcount);
}

void flexarray_free(flexarray f) {
    free(f->items);
    free(f);
}
