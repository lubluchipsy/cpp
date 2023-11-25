#include "container.hpp"
#include <iostream>


int main()
{
    Container c;
    c.push_back(42);
    c.push_back(2);
    std::cout << c.get_capacity()<< std::endl;
    std::cout << c.get_size() << std::endl;
    std::cout << c[0] << " ";
    std::cout << c[1];
    return 0;
}