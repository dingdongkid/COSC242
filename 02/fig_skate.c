#include <stdio.h>
#include <stdlib.h>

int main(void) {
    double s1;
    double s2;
    double s3;
    int return_code;

    printf("Enter three integers: \n");
    fflush(stdout);
    return_code = scanf("%lg %lg %lg", &s1, &s2, &s3);
    if (return_code != 3) {
        printf("scanf returns code %d \n", return_code);
        return EXIT_FAILURE;
    }  else {
        printf("Overall score is: ");
        if (s1 <= s2 && s1 <= s3) {
            printf("%.2f\n", (s2 + s3)/2);
        } else if (s2 <=1 && s2 <=3) {
            printf("%.2f\n", (s1 + s3)/2);
        } else {
            printf("%.2f\n", (s1 + s2)/2);
        }
    }
    return EXIT_SUCCESS;
}
