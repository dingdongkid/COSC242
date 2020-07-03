#include <stdio.h>
#include <stdlib.h>

void display_repeats(int *a, int s) {
    int i = 0;
    int *store;
    store = malloc(s * sizeof store[0]);
    for(i = 0; i < s; i++) {
        store[i] = 0;
    }
    
    for(i = 0; i < s; i++) {
        store[a[i]]++;
    }

    for(i = 0; i < s; i++) {
        if(store[i] > 1) {
            printf("%d occurs %d times\n", i, store[i]);
        }
    }
    free(store);
}
    
    

int main(void) {
    int array_size = 0;
    int *my_dynamic_array;
    int i = 0;

    printf("Enter the size of the array:\n");
    scanf("%d", &array_size);

    /* initialise the array to the appropriate size */
    my_dynamic_array = malloc(array_size * sizeof my_dynamic_array[0]);
    if (NULL == my_dynamic_array) {
        fprintf(stderr, "memory allocation failed!\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < array_size; i++) {
        my_dynamic_array[i] = rand() % array_size;
    }

    printf("What's in the array:\n");
    for (i = 0; i < array_size; i++) {
        printf("%d ", my_dynamic_array[i]);
    }
    printf("\n");
    display_repeats(my_dynamic_array, array_size);

    /* release the memory associated with the array */
    free(my_dynamic_array);

    return EXIT_SUCCESS;
}
