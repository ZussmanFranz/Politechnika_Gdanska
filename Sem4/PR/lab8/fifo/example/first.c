#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>

int main()
{
    int x = 0;
    int f = 0;
    
    puts("Otwieram");
    f = open("test", O_WRONLY);
    sleep(10);
    
    puts("Wysylam i koncze");
    write(f, &x, sizeof(x));
    
    close(f) ;
}