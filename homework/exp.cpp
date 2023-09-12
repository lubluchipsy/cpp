#include <iostream>

int main()
{
    const auto epsilon = 0.00000001;
    auto e = 1.0;
    auto summand = 1.0;
    for (auto k = 1; ; k++)
    {
        summand = summand / k;
        e += summand;
        if (summand < epsilon)
        {
            std::cout << "e = " << e;
            break;
        }
        
    }
}