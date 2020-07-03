#include <stdio.h>
#include <stdlib.h>

int is_prime(int candidate) {
    int n;
    for(n = 2; n < candidate; n++) {
        if(candidate%n == 0) {
            return 0;
        }
    }
    return 1;
}

int main(void) {
    int candidate = 2;
    int num_printed = 0;
    int count = 1;
    while (num_printed < 200) {
        if (is_prime(candidate) == 1) {
            printf("%5d", candidate);
            num_printed++;
            if(count++ == 10) {
                printf("\n");
                count = 1;
            }
        }
        candidate++;
    }
    return EXIT_SUCCESS;
}
