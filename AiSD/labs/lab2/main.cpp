#include<iostream>
#include<string>
#include<vector>

bool cmp_rec(std::string s1, std::string s2, size_t i)
{
    if (i < s1.size())
    {
        if (s1[i] > s2[i])
        {
            return true;
        }
        else if (s1[i] < s2[i])
        {
            return false;
        }
        else
        {
            return cmp_rec(s1, s2, i + 1);
        }
    }
    else
    {
        return true;
    }
}
bool bigger(std::string s1, std::string s2)
{
    if (s1.size() > s2.size())
    {
        return true;
    }
    else if (s1.size() < s2.size())
    {
        return false;
    }
    else
    {
        return cmp_rec(s1, s2, 0);
    }
}

int partition(std::vector<std::string>& arr, int low, int high) {
    std::string pivot = arr[high]; // Choosing the last element as the pivot
    int i = low - 1; // Index of the smaller element

    for (int j = low; j < high; j++) {
        // If the current element is smaller than or equal to the pivot
        if (!bigger(arr[j], pivot)){
            i++; // Increment index of smaller element
            std::swap(arr[i], arr[j]);
        }
    }

    std::swap(arr[i + 1], arr[high]); // Swap pivot to its correct position
    return i + 1;
}

void quickSort(std::vector<std::string>& arr, int low, int high) {
    if (low < high) {
        // Partitioning index
        int pi = partition(arr, low, high);

        // Separately sort elements before and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main()
{
    std::vector<std::string> numbers_i;

    std::string take;

    int n_liczb;
    std::cin >> n_liczb;

    for (int i = 0; i < n_liczb; i++)
    {
        std::cin >> take;
        numbers_i.push_back(take);   
    }
    
    quickSort(numbers_i, 0, numbers_i.size() - 1);

    //result
    for (size_t i = 0; i < numbers_i.size(); i++)
    {
        std::cout << '\n' << numbers_i[i];
    }
    
}