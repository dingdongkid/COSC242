#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"
#include "flexarray.h"

struct flexarrayrec {
    int capacity;
    int itemcount;
    int *items;
};

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

static void merge(int *array, int *workspace, int n) {
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

static void merge_sort(int *a, int *w, int n) {
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

void flexarray_sort(flexarray f) {
    int *workspace = emalloc(f->capacity * sizeof f->itemcount);
    merge_sort(f->items, workspace, f->itemcount);
    free(workspace);
}

void flexarray_free(flexarray f) {
    free(f->items);
    free(f);
}
