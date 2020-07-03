#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "mylib.h"

struct queue {
    int *items;
    int head;
    int capacity;
    int num_items;
};

/*
void *emalloc(size_t s) {
    void *result = malloc(s);
    if(NULL == result) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    return result;
}
*/

queue queue_new() {
    queue q = emalloc(sizeof *q);
    q->capacity = 5;
    q->head = 0;
    q->num_items = 0;
    q->items = emalloc(q->capacity * sizeof q->items[0]);
    return q;
}

void enqueue(queue q, double item) {
    if(q->num_items < q->capacity) {
        int i = (q->head + q->num_items) % q->capacity;
        q->items[i] = item;
        q->num_items++;
    }
}

double dequeue(queue q) {
    double d;
    if(q->num_items > 0) {
        d = q->items[q->head];
        q->head++;
        if(q->head >= q->capacity) {
            q->head = 0;
        }
        q->num_items--;
        return d;
    } else {
        fprintf(stderr, "no items to remove\n");
        exit(EXIT_FAILURE);
    }
}

void queue_print(queue q) {
    int i;
    int j = q->head;
    for(i = 0; i < q->num_items; i++) {
        printf("%d\n", q->items[j++]);
        if(j >= q->capacity) {
            j = 0;
        }
    }
}

int queue_size(queue q) {
    return q->num_items;
}

queue queue_free(queue q) {
    free(q->items);
    free(q);
    return q;
}
