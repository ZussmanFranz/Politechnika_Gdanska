#include<unistd.h>
#include<stdio.h>
#include<string.h>

#define ODCZYT 0
#define ZAPIS 1
#define INPUT_SIZE 100

char* capitalize(const char* str, int len) {
    static char new_str[INPUT_SIZE];  // Make it static

    strncpy(new_str, str, INPUT_SIZE - 1);  // Use strncpy for safety
    new_str[INPUT_SIZE - 1] = '\0';         // Ensure null termination

    for (int i = 0; i < len && new_str[i] != '\0'; i++) {
        if (new_str[i] >= 'a' && new_str[i] <= 'z') {
            new_str[i] -= 32;  // Convert to uppercase
        }
    }

    return new_str;
}

int main()
{
    int potok[2];
    char str[INPUT_SIZE];

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
        puts("String passed to Process 2");

        close(potok[ZAPIS]);
    }
    else
    {
        puts("Process 2 (string processing)");
        
        read(potok[ODCZYT], str, sizeof(str));

        printf("Process 2 got string %s\n", str);

        // fork
        puts("New process");
        pipe(potok);
        puts("Fork");
        
        if (fork()){
            // processing
            char* new_str = capitalize(str, INPUT_SIZE);
            printf("processed %s to %s\n", str, new_str);

            // send str
            write(potok[ZAPIS], new_str, sizeof(new_str));

            close(potok[ZAPIS]);
            close(potok[ODCZYT]);
        } else {
            puts("Process 3 started");

            read(potok[ODCZYT], str, sizeof(str));

            printf("String in process 3: %s\n", str);

            // print str
            close(potok[ZAPIS]);
            close(potok[ODCZYT]);
        }
    }

    puts("Program pipes konczy");
}