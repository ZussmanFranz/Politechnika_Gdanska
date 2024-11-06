
#include <cstdio>
#include <cstdlib>

int main()
{
    printf("położenie kodu: %p\n", (void*) main);
    printf("położenie sterty(heap): %p\n", (void*) malloc(1));
    int x = 3;
    printf("położenie stosu: %p\n", (void*) &x);
    return x;
}