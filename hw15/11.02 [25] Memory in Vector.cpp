#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>

int main()
{
    std::vector <int> v1;
    assert(v1.capacity() == 0); //empty

    v1.push_back(42);
    std::cout << v1.capacity() << std::endl; // size = 1, capacity = 1 

    v1.push_back(42);
    std::cout << v1.capacity() << std::endl; // size = 2, capacity = 2, 2^0 = 1 added

    v1.push_back(42);
    std::cout << v1.capacity() << std::endl; // size = 3, capacity = 4, 2^1 = 2 added

    v1.push_back(42);
    std::cout << v1.capacity() << std::endl; // size = 4, capacity = 4, no need to add anything

    v1.push_back(42);
    std::cout << v1.capacity() << std::endl; // size = 5, capasity = 8, 2^2 = 4 added

// when out of memory, capacity is growing by powers of 2

// Investigating reserve()

    std::size_t begin_capasity = 5;
    std::vector <int> v2;
    v2.reserve(begin_capasity);     // capacity = 5

    for (auto i = 0; i < begin_capasity; i++)
    {
        v2.push_back(i);    // capacity == size, no place for more objects
    }

    assert(v2.capacity() == begin_capasity);    // capacity == size, no place for more objects

    v2.push_back(begin_capasity);    // one more object added
    std::cout << v2.capacity() << std::endl;  // capacity = 2*5 = 10; capacity became 2 times bigger

    for (auto i = begin_capasity + 1; i < 2 * begin_capasity; i++)
    {
        v2.push_back(i);
    }

    assert(v2.capacity() == 2 * begin_capasity);   // capacity == size, no place for more objects
        
    v2.push_back(2*begin_capasity);    // one more object added
    std::cout << v2.capacity() << std::endl;   // capacity = 2*10 = 20; capacity became 2 times bigger

    // each time we run out of capacity, it multiplies by 2. Therefore capacity always equals begin_capasity*n

    return 0;
}