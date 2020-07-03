#include <stdio.h>
#include <stdlib.h>
int main(void) {
    int i = 5;
    int *p;
    
    printf("i is %d, the address of i is %p\n", i,(void *) &i);

    p = &i; /* p is now storing the address of i (whatever that is) */
    printf("p is %p, what’s stored at p is %d\n", (void *) p, *p);

    *p = 6; /* make the value at memory location p 6 */
    printf("what’s stored at p is %d, i is also %d\n", *p, i);

    return EXIT_SUCCESS;
}
