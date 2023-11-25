#include <iostream>

int * bin_search(int * arr, int a, int left, int right)
{
    if (right == 0)
    {
        return nullptr;
    }

    if (right == 1)
    {
        return (arr[0] == a ? arr : nullptr);
    }

    while (left < right)
    {
        auto mid = left + (right - left)/2;
        if (arr[mid] < a)
        {
            left = mid + 1;
        }
        else
        {
            right = mid;
        }
    }
    return (arr[left] == a ? (arr + left) : nullptr);
}

int main()
{
    const auto size = 7;

    auto a = new int[size]{1, 3, 4, 5, 6, 7, 8};

    for(auto i = a[0] - 1; i <= a[size - 1] + 1; ++i)
    {
        if(auto ptr = bin_search(a, i, 0 , size); ptr)
        {
            std::cout << "Element " << i << " found at index " << ptr - a << "\n";
        }
        else
        {
            std::cout << "Element " << i << " not found\n";
        }
    }

    return 0;
}