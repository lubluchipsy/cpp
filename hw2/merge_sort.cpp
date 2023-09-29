#include <iostream>

void merge(int* arr, int left, int mid, int right)
{
    auto size = right - left + 1;

    auto* res = new int[size];

    auto size1 = mid - left + 1;
    auto size2 = right - mid;

    auto i = 0;
    auto j = 0;
    auto k = 0;

    while (i < size1 && j < size2)
    {
        if (arr[left + i] <= arr[mid+1 + j])
        {
            res[k] = arr[left + i];
            i++;
        }
        else
        {
            res[k] = arr[mid+1 + j];
            j++;
        }
        k++;
    }

    while (i < size1)
    {
        res[k] = arr[left + i];
        i++;
        k++;
    }

    while (j < size2)
    {
        res[k] = arr[mid+1 + j];
        j++;
        k++;
    }

    for (auto i = 0; i < size; i++)
    {
        arr[left + i] = res[i];
    }

    delete[] res;
}

void mergesort(int* arr, int left, int right)
{
    if (right > left)
    {
        auto mid = left + (right - left) / 2;
        mergesort(arr, left, mid);
        mergesort(arr, mid + 1, right);
        merge(arr, left, mid, right);
        }
}

int main()
{
    int size{};
    std::cout << "Enter array size: ";
    std::cin >> size;
    std::cout << "Enter the array: ";
    auto* arr = new int[size];
    
    for (auto i = 0; i < size; i++)
    {
         std::cin >> arr[i];
    }

    mergesort(arr, 0, size - 1);

    std::cout << "Sorted array: ";

    for (auto i = 0; i < size; i++)
    {
         std::cout << arr[i] << " ";
    }
    
    
    return 0;
}