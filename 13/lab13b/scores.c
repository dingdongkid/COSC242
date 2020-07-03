#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n;
    double s1, s2, s3;

    int winner = 0;
    double score;
    double high = 0;
    
    while(4 == scanf("%d%lg%lg%lg", &n, &s1, &s2, &s3)) {
        if(s1 <= s2 && s1 <= s3) {
            score = (s2 + s3)/2;
        } else if (s2 <= s1 && s2 <= s3) {
            score = (s1 + s3)/2;
        } else {
            score = (s1 + s2)/2;
        }
        if(score > high) {
            winner = n;
            high = score;
        }
    }

    printf("%d\n", winner);

    return EXIT_SUCCESS;
}
