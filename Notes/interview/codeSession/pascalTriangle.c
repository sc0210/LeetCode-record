/* pascal triangle 20250903 */

#include "stdio.h"

void pac(int N)
{
    int pac[N][N];
    printf("Passcal Triangle of N=%d\n", N);

    for (int i = 1; i <= N; i++) {
        printf("N=%d", i);
        // print space in front of the first element
        for (int k = 0; k < N - i; k++)
            printf("   ");

        for (int j = 1; j <= i; j++) {
            if (i == 1 || j == 1 || j == i)
                pac[i - 1][j - 1] = 1;
            else
                pac[i - 1][j - 1] = pac[i - 2][j - 2] + pac[i - 2][j - 1];

            printf("%6d", pac[i - 1][j - 1]);
        }
        printf("\n");
    }
    printf("\n");
}

int main()
{
    pac(5);
    pac(10);
    pac(20);
    return 0;
}