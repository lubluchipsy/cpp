#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <iterator>
#include <numeric>
#include <random>
#include <vector>

void print(std::vector < int > & v)
{
    for(auto e:v){std::cout << e << " ";};
    std::cout << std::endl;
}


int main()
{
    constexpr std::size_t size = 10; 

    std::vector < int > v1(size);

	std::iota(std::begin(v1), std::end(v1), 0); // v1 = 0 1 2 3 4 5 6 7 8 9 

    std::for_each_n(std::begin(v1), 3, [](auto & n){n *= 7;}); // v1 = 0 7 14 3 4 5 6 7 8 9

    assert(std::count_if(std::begin(v1), std::end(v1), [](auto n){return n % 7 == 0;}) == 4);
    
    std::shift_left(std::begin(v1), std::end(v1), 3); // v1 = 3 4 5 6 7 8 9 7 8 9 
    print(v1);

    std::rotate(std::begin(v1), (std::begin(v1) + std::size(v1)/2), std::end(v1)); // v1 = 8 9 7 8 9 3 4 5 6 7
    print(v1);

    std::fill_n(std::begin(v1), 3, 1); // v1 = 1 1 1 8 9 3 4 5 6 7 

    std::vector < int > v2;
    std::unique_copy(std::begin(v1), std::end(v1), std::back_inserter(v2)); // v2 = 1 8 9 3 4 5 6 7 

    std::replace_if(std::begin(v2), std::end(v2), [](auto n){return n % 3 == 0;}, 2); // v2 = 1 8 2 2 4 5 2 7
    print(v2);

    std::iter_swap(std::begin(v2), std::end(v2)- 1); //v2 = 7 8 2 2 4 5 2 1 
    print(v2);

    std::vector < int > v3(4);
    std::copy_n(std::begin(v2), 4, std::begin(v3));
    print(v3);

    assert(*std::mismatch(std::begin(v2), std::end(v2), std::begin(v3), std::end(v3)).first == 4);

    return 0;
}