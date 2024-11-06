#include <cstdio>
#include <iostream>

using namespace std;

bool check() 
{
    int size;
    cin >> size;
    char* str = new char[size * size]; // Assuming maximum size of the string is 100 characters
    cin >> str;

    int n = 0;
    int n_prev = 0;
    int actual_size = 0;
    do {
        int counter = 0;
        int current = n * size;
        bool encountered = false;
        for (int i = 0; i < size; i++)
        {
            if (str[current + i] == '1') 
            {
                counter++;
                if (i != n_prev && !encountered)
                {
                    n_prev = n;
                    n = i;
                    encountered = true;
                }
            }
        }
        if (counter != 2) { return 0; }
        actual_size++;
    } while ( n != 0 );

    if (actual_size == size) { return 1; }
    return 0;
}

int main()
{
    int count;

    cin >> count;
    for (int i = 0; i < count; i++) {
        cout << check() << endl;
    }

    return 0;
}