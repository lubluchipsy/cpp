#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
 
template <typename T>
std::list <T> sort_list(std::list <T> & l)
{
    std::vector <std::reference_wrapper<T>> v(l.begin(), l.end());
    std::sort(v.begin(), v.end());

    std::list <T> sorted;
    for (auto iter{v.begin()}; iter != v.end(); iter++)
    {
        sorted.push_back(*iter);
    }

    return sorted;
}

int main()
{
    std::list <int> l{2, 1, 6, 3, 0};
    l = sort_list(l);

    for (auto iter{l.begin()}; iter != l.end(); iter++)
    {
        std::cout << *iter << " ";
    }
    std::cout << std::endl;
    
    return 0;
}
