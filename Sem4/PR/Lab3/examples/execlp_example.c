#include <unistd.h>
#include <stdio.h>

int main()
{
    if (fork() == 0){
        printf("proces potomny pid: %d ppid: %d\n", getpid(), getppid());
        execlp("ps", "ps", "-u", "zussman", "--forest", NULL);
        return 0;
    }
    else {
        printf("proces macierzysty pid: %d ppid: %d\n", getpid(), getppid());
        sleep(5);
        return 0;
    }
}