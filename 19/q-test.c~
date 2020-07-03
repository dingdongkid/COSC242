#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int main(void) {
    double i;
    queue q = queue_new();

    for(i = 0; i < 6; i++) {
        enqueue(q, i);
        queue_size(q);
    }
    
    queue_print(q);
    dequeue(q);
    queue_print(q);
    enqueue(q, 6);
    queue_print(q);
    queue_free(q);

    return EXIT_SUCCESS;
}
    
