#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

#define INPUT_SIZE 100

int main() {
    int f;
    char str[INPUT_SIZE];

    puts("Program FIFO writer startuje");
    
    f = open("fifo1", O_WRONLY);
    
    puts("Enter your string here: ");
    scanf("%s", str);
    printf("String entered: %s\n", str);
    
    write(f, str, INPUT_SIZE);
    puts("String passed to reader");
    
    close(f);
    
    puts("Writer kończy");
    return 0;
}