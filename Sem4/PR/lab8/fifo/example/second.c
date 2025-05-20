#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>

int main ()
{
    int f;
    int x = 0;
    
    puts("Otwieram");
    f = open("test", O_RDONLY);
    read(f, &x, sizeof(x));
    
    puts("Odebralem i koncze");
    close(f);
}