#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define INPUT_SIZE 100

void capitalize(char* str) {
    for(int i = 0; str[i]; i++) {
        str[i] = toupper(str[i]);
    }
}

int main() {
    int f1, f2;
    char str[INPUT_SIZE];
    
    puts("Program FIFO reader startuje");
    
    f1 = open("fifo1", O_RDONLY);
    read(f1, str, INPUT_SIZE);
    close(f1);
    
    printf("Received string: %s\n", str);
    capitalize(str);
    printf("Capitalized: %s\n", str);
    
    puts("Reader kończy");
    return 0;
}