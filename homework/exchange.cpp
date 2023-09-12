#include <iostream>

int main()
{
    double x{};
    double y{};
    std::cout << "Input x\n";
    std::cin >> x;
    std::cout << "Input y\n";
    std::cin >> y;
    x += y;
    y = x - y;
    x -= y;
    std::cout << "x = " << x << "\n" << "y = " << y;

    

}