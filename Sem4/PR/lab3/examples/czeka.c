#include <unistd.h>
#include <stdio.h>

int main()
{
    int pid = fork();

    if (pid == 0){
        // proces potomny
        printf("zglasza sie proces potomny pid: %d ppid: %d\n", getpid(), getppid());
        sleep(10);
        printf("proces potomny konczy dzialanie\n");
        return 0;
    }else {
        // proces macierzysty
        printf("zglasza sie proces macierzysty pid: %d ppid: %d\n", getpid(), getppid());
        sleep(5);
        printf("proces macierzysty konczy dzialanie\n");
        return 0;
    }
}