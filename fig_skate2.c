#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n;
    double a;
    double b;
    double c;
    
    int winner = 0;
    double score;
    double high = 0;

    printf("Reading scores.\n");
    fflush(stdout);
    while (4 == scanf("%d%lg%lg%lg", &n, &a, &b, &c)) {
        if (a <= b && a <= c) {
            score = (b + c)/2;
        } else if (b <= a && b <= c) {
            score = (a + c)/2;
        } else {
            score = (a + b)/2;
        }
        printf("Competitor %d has a score of %.1f.\n", n, score);
        if (score > high) {
            winner = n;
            high = score;
        }
    }

    printf("\n%d wins with a score of %.1f.\n", winner, high);
    return EXIT_SUCCESS;
}
