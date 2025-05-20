#include <unistd.h>
#include <stdio.h>

#define ODCZYT 0
#define ZAPIS 1
#define WORKERS 10
#define MAX_PROCESSES 3  // Number of processes allowed in critical section

int semafor[2];

void LOCK()
{
    int x;
    read(semafor[ODCZYT], &x, sizeof(x));
}

void UNLOCK()
{
    int x = 0;
    write(semafor[ZAPIS], &x, sizeof(x));
}

void worker(int id, int potok_k)
{
    int x = 0, i;
    printf("Worker %d startuje\n", id);
    
    LOCK();

    for (i = 0; i < 7; i++)
    {
        printf("[%d]", id);
        fflush(stdout);
        sleep(1);
    }
    
    UNLOCK();
    
    printf("Worker %d konczy\n", id);
    write(potok_k, &x, sizeof(x));
}

int main()
{
    int potok_konczacy[2], i, x;

    pipe(potok_konczacy);
    pipe(semafor);
    
    for (i = 0; i < MAX_PROCESSES; i++) {
        UNLOCK();
    }
    
    for (i = 0; i < WORKERS; i++)
    {
        if (!fork())
        {
            worker(i, potok_konczacy[ZAPIS]);
            return 0;
        }
    }

    for (i = 0; i < WORKERS; i++) {
        read(potok_konczacy[ODCZYT], &x, sizeof(x));
    }

    puts("\nkoniec");
    return 0;
}