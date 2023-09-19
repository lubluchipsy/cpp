#include <iostream>

int main()
{
    int size{};
    std::cout << "Enter array size: ";
    std::cin >> size;
    std::cout << "Enter " << size << " integer values: ";
    auto arr = new int[size];

    for (auto i = 0; i < size; i++)
    {
        std::cin >> arr[i];
    }

    for (auto j = 1; j < size; j++)
    { 
       auto key = arr[j];
       auto i = j - 1;

       while ((i >= 0) & (arr[i] > key))
       {
        arr[i+1] = arr[i];
        i -=1;
       }

       arr[i+1] = key;
    }

    std::cout << "Sorted array: ";

    for (auto i = 0; i < size; i++)
    {
        std::cout << arr[i] << ' ';
    }

    delete[] arr;

    return 0;
}