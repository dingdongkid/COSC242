#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ARRAY_SIZE 10

int main(void) {
    int n;
    double a, b, c;

    double judge1[ARRAY_SIZE];
    double judge2[ARRAY_SIZE];
    double judge3[ARRAY_SIZE];

    double total1 = 0, total2 = 0, total3 = 0;
    double mean1, mean2, mean3;
    
    double variance1, variance2, variance3;
    double sd1, sd2, sd3;

    int count = 0;
    int i;

    printf("Reading scores.\n");
    fflush(stdout);
    /* Reading scores. */
    while (4 == scanf("%d%lg%lg%lg", &n, &a, &b, &c)) {
        judge1[count] = a;
        judge2[count] = b;
        judge3[count] = c;
        count++;
    }

    /* Calculating mean */
    for(i = 0; i < count; i++) {
        total1 += judge1[i];
        total2 += judge2[i];
        total3 += judge3[i];
    }
    
    mean1 = total1/count;
    mean2 = total2/count;
    mean3 = total3/count;

    total1 = 0;
    total2 = 0;
    total3 = 0;

    /* Calculating SD */
    for(i = 0; i < count; i++) {
        judge1[i] = pow((judge1[i] - mean1), 2);
        judge2[i] = pow((judge2[i] - mean2), 2);
        judge3[i] = pow((judge3[i] - mean3), 2);
    }

    for(i = 0; i < count; i++) {
        total1 += judge1[i];
        total2 += judge2[i];
        total3 += judge3[i];
    }
    
    variance1 = total1/(count-1);
    variance2 = total2/(count-1);
    variance3 = total3/(count-1);

    sd1 = sqrt(variance1);
    sd2 = sqrt(variance2);
    sd3 = sqrt(variance3);

    printf("Judge 1: Average = %.1f, SD = %.1f\n", mean1, sd1);
    printf("Judge 2: Average = %.1f, SD = %.1f\n", mean2, sd2);
    printf("Judge 3: Average = %.1f, SD = %.1f\n", mean3, sd3);
    return EXIT_SUCCESS;
}
