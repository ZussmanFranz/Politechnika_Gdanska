#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h> 


int main()
{
    int pid = fork();
    if (pid == 0){
        printf("proces potomny pid: %d ppid: %d\n", getpid(), getppid());
        sleep(5);
        execlp("ps", "-u zussman", "-l", "--forest", NULL);
        return 0;
    }
    else {
        waitpid(pid, NULL, 0);
        printf("proces potomny %d zakonczony\n", pid);
        return 0;
    }
}