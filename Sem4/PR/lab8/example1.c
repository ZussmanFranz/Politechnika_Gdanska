#include<unistd.h>
#include<stdio.h>

#define ODCZYT 0
#define ZAPIS 1

int main()
{
    int potok[2];
    int x;

    puts("Program pipes startuje");
    puts("Tworze potok");
    pipe(potok);
    puts("fork");

    if(fork())
    {
        puts("Proces macierzysty");
        close(potok[ZAPIS]);
        puts("Czekam na proces potomny");
        read(potok[ODCZYT], &x, sizeof(x));
        printf("Proces macierzysty otrzymal %d\n",x);
        close(potok[ODCZYT]);
    }
    else
    {
        puts("Proces potomny");
        close(potok[ODCZYT]);
        x=10;
        sleep(10);
        write(potok[ZAPIS],&x,sizeof(x));
        puts("Proces potomny wyslal");
        close(potok[ZAPIS]);
    }

    puts("Program pipes konczy");
}