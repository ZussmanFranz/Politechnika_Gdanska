#include <iostream>
using namespace std;

int main()
{
    int variable = 0;
    string str = "hello!";

    for (int i = 0; i < str.size(); i++)
    {
        cout << str[i] << endl;
    }

    cout << "Size of int: " << sizeof(long long) << endl;
    cout << "Size of variable int: " << sizeof(variable) << endl;
    cout << "Size of variable string: " << sizeof(str) << endl;
    cout << "Size of the first character: " << sizeof(str[0]) << endl;
    return 0;
}