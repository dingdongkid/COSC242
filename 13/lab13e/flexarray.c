#include <stdio.h>
#include <stdlib.h>
#include "flexarray.h"

struct flexarrayrec {
    int capacity;
    int itemcount;
    int *items;
};

static void *erealloc(void *p, size_t s) {
    void *result = realloc(p, s);
    if (NULL == result) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    return result;
}

static void selection_sort(int *a, int n) {
    int i, p, value, low, temp, j;
    for (p = 0; p < n-1; p++) {
        low = p;
        value = a[p];
        for(i = p; i < n; i++) {
            if (a[i] < value) {
                low = i;
                value = a[i];
            }
        }
        temp = a[p];
        a[p] = a[low];
        a[low] = temp;
        
        if(p+1 == n/2) {
            for(j = 0; j < n; j++) {
                fprintf(stderr, "%d\n", a[j]);
            }
        }
    }
}

flexarray flexarray_new() {
    flexarray result = malloc(sizeof *result);
    if (NULL == result) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    result->capacity = 2;
    result->itemcount = 0;
    result->items = malloc(result-> capacity * sizeof result->items[0]);
    if (NULL == result->items) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
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

void flexarray_sort(flexarray f) {
    selection_sort(f->items, f->itemcount);
}

void flexarray_free(flexarray f) {
    free(f->items);
    free(f);
}
    
