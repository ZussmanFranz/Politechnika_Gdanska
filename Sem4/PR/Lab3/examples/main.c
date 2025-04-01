#include <unistd.h>
#include <stdio.h>

int main()
{
    int pid;
    printf("Proces uruchomiony %d\n", getpid());
    pid = fork();

    if (pid == -1){
        perror("Blad utworzenia procesu potomnego!");
        return 1;
    }
    else if (pid == 0){
        printf("Zglasza sie proces potomny %d\n", getpid());
        sleep(10);
    }
    else {
        printf("Zglasza sie proces macierzysty %d. Potomek %d\n", getpid(), pid);
        sleep(9);
    }
}