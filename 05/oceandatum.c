#include <stdio.h>
#include <stdlib.h>

#define OCEAN_MAX 41981

struct ocean_datum {
    int x; /* grid-reference east-west                                   */
    int y; /* grid-reference north-south                                 */
    double conc; /* concentration of O_2 in mL/L found at grid-ref (x,y) */
};

void print_ocean_datum(struct ocean_datum *o) {
    printf("%d %d %.4f\n", o->x, o->y, o->conc);
}

int read_ocean_datum(struct ocean_datum *o) {
    return 3 == scanf("%d %d %lg", &o->x, &o->y, &o-> conc);
}

int main(void) {
    struct ocean_datum ocean_data[OCEAN_MAX];
    int num_items;
    int i;
    double key;
    int index;

    num_items = 0;
    while (num_items < OCEAN_MAX && read_ocean_datum(&ocean_data[num_items])) {
        num_items++;
    }

  /* For all positions except the first */
    for(i = 1; i < num_items; i++) {
        /* Pull out item p and store it */
        key = ocean_data[i].conc;

        /* Move each item left of p, and greater than key, one to the right */
        index = i-1;
        while (index >= 0 && ocean_data[index].conc > key) {
            ocean_data[index+1].conc = ocean_data[index].conc;
            index--;
        }

        /* Place key in the leftmost vacated position */
        ocean_data[index+1].conc = key;
        /* sorting code*/
    }

    for (i = 0; i < num_items; i++) {
        print_ocean_datum(&ocean_data[i]);
    }

    return EXIT_SUCCESS;
}
