#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main (void) {

    /* variable declarations*/
    int i = 0;
    int f = 0;
    int g = 1;
    int temp = 0;
    int line_count = 1;
    
    /* for loop */
    for (i = 0; i < 40; i++) {
        printf("%d, ", g);
        temp = g;
        g += f;
        f = temp;
        if(line_count++ == 5) {
            printf("\n");
            line_count = 1;
        }
    }

    return EXIT_SUCCESS; /* defined in stdlib.h */
}
