#include <iostream>

int main()
{
    const auto maxnum= 1000;
    for (auto num = 100; num < maxnum; num++) 
    {
        auto a = num % 10;
        auto b = (num / 10) % 10; 
        auto c = num / 100;
        if ((a*a*a + b*b*b + c*c*c) == num)
            {
                std::cout << num <<" \n";
            }
    }     
}