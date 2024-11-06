#include <cstdio>
#include <iostream>

using namespace std;

bool check() 
{
    int size;
    cin >> size;
    getchar(); //skip space
    char** graph = new char*[size];
    for (int i = 0; i < size; i++) {
        graph[i] = new char[size];
        for (int j = 0; j < size; j++) {
            graph[i][j] = getchar();
        }
    }

    //diagnostics:
    // for (int i = 0; i < size; i++) {
    //     for (int j = 0; j < size; j++) {
    //         cout << graph[i][j];
    //     }
    //     //cout << '\n';
    // }
    // cout << '\n';

    int result = 1;

    for (int i = 0; (i < size) && (result == 1); i++) {
        for (int j = 0; (j < size) && (result == 1); j++) {
            if (i == j) {
                continue;
            }

            for (int k = 0; (k < size) && (result == 1); k++) {
                if ((i == k) || (j == k)) {
                    continue;
                }

                for (int q = 0; (q < size) && (result == 1); q++) 
                {
                    if ((i == q) || (j == q) || (k == q)) {
                        continue;
                    }

                    if ((graph[i][j] == '1') && (graph[i][k] == '1') && (graph[i][q] == '1')) 
                    {   
                        if ((graph[j][k] == '0') && (graph[j][q] == '0') && (graph[k][q] == '0')) {
                            result = 0; //contains claw
                            break;
                        }
                    }
                    else if ((graph[j][i] == '1') && (graph[j][k] == '1') && (graph[j][q] == '1')) 
                    {
                        if ((graph[i][k] == '0') && (graph[k][q] == '0') && (graph[i][q] == '0')) {
                            result = 0; //contains claw
                            break;
                        }
                    }
                    else if ((graph[k][i] == '1') && (graph[k][j] == '1') && (graph[k][q] == '1')) 
                    {
                        if ((graph[i][j] == '0') && (graph[i][q] == '0') && (graph[k][q] == '0')) {
                            result = 0; //contains claw
                            break;
                        }
                    }
                    else if ((graph[q][i] == '1') && (graph[q][k] == '1') && (graph[q][j] == '1')) 
                    {
                        if ((graph[i][j] == '0') && (graph[i][k] == '0') && (graph[k][j] == '0')) {
                            result = 0; //contains claw
                            break;
                        }
                    }
                }
            }
        }
    }

    for (int i = 0; i < size; i++) {
        delete [] graph[i];
    }
    delete [] graph;

    return result; //doesn't contain claw
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