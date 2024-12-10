#include <stdio.h>

int main()
{
    int S1 = 0;
    int S2 = 0;
    int a = 0;
    int n = 100;

    for (int i = 1; i <= n; i++)
    {
        a += i;
        S1 += a;
        S2 += i * (i + 1) / 2;
    }

    printf("S1 = %d\nS2 = %d\n", S1, S2);

    return 0;
}