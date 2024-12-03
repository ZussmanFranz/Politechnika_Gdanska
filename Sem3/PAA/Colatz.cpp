#include "stdio.h"

int main(){
    int Nsteps = 0;
    int k;

    printf("enter k number for Collatz algorithm: ");
    scanf("%d", &k);

    do {
        if (k % 2 == 0){
            k /= 2;
        } else {
            k = 3 * k + 1;
        }

        printf("\t%d\n", k);

        Nsteps++;
    } while(k != 1);

    printf("Nsteps: %d", Nsteps);

    return 0;
}