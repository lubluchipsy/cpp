#include <iostream>

void merge(int* arr, int left, int mid, int right)
{
    auto size1 = mid - left + 1;
    auto size2 = right - mid;

    auto* arr1 = new int[size1];
    auto* arr2 = new int[size2];

    for (auto i = 0; i < size1; i++)
    {
        arr1[i] = arr[left + i];
    }

    for (auto i = 0; i < size2; i++)
    {
        arr2[i] = arr[mid + 1 + i];
    }

    auto i = 0;
    auto j = 0;
    auto k = left;

    while (i < size1 && j < size2)
    {
        if (arr1[i] <= arr2[j])
        {
            arr[k] = arr1[i];
            i++;
        }
        else
        {
            arr[k] = arr2[j];
            j++;
        }
        k++;
    }

    while (i < size1)
    {
        arr[k] = arr1[i];
        i++;
        k++;
    }

    while (j < size2)
    {
        arr[k] = arr2[j];
        j++;
        k++;
    }

    delete [] arr1;
    delete [] arr2;
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

