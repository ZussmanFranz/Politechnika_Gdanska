#include<unistd.h>
#include<stdio.h>

#define ODCZYT 0
#define ZAPIS 1
#define INPUT_SIZE 100

char* capitalize(char* str, int len) {
    for (int i = 0; i < len; i++) {
        // process
    }
}

int main()
{
    int potok[2];
    char* str[INPUT_SIZE];

    puts("Program pipes startuje");
    puts("Tworze potok");
    pipe(potok);
    puts("fork");

    if(fork())
    {
        puts("Process 1:\nEnter your string here: ");

        scanf("%s", str);
        
        printf("String entered: %s\n", str);

        close(potok[ODCZYT]);
        
        write(potok[ZAPIS], str, sizeof(str));
        puts("String passed to Process 2")

        close(potok[ZAPIS]);
    }
    else
    {
        puts("Process 2 (string processing)");
        
        read(potok[ODCZYT], str, sizeof(str));

        printf("Process 2 got string %s\n", str);

        // processing
        puts("processed")

        // fork
        puts("New process")
        pipe(potok);
        puts("Fork")
        
        if (fork()){
            // send str
            close(potok[ZAPIS]);
            close(potok[ODCZYT]);
        } else {
            // print str
            close(potok[ZAPIS]);
            close(potok[ODCZYT]);
        }
    }

    puts("Program pipes konczy");
}