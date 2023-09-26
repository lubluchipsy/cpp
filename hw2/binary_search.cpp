#include <iostream>

int bin_search(int arr[], int a, int left, int right)
{
    while (left!=right)
    {
        auto mid = left + (right - left)/2;
        if (arr[mid] >= a)
        {
            right = mid;
            bin_search(arr, a, left, right);
        }
        else
        {
            left = mid + 1;
            bin_search(arr, a, left, right);
        }
    }
    if (arr[left] == a)
    {
        return left;
    }
    else
    {
        return -1;
    }
}

int main()
{
    int size{};
    std::cout << "Enter array size: ";
    std::cin >> size;

    std::cout << "Enter sorted array: ";
    auto* arr = new int[size];
    for (auto i = 0; i < size; i++)
    {
         std::cin >> arr[i];
    }
    
    int a{};
    std::cout << "Enter the number you are looking for: ";
    std::cin >> a;
    
    auto result = bin_search(arr, a, 0, size-1);
    
    if (result == -1)
    {
        std::cout << "Number not found in the array";
    }
    else
    {
        std::cout << "The number is on position " << bin_search(arr, a, 0, size-1);
    }
    
    return 0;
}