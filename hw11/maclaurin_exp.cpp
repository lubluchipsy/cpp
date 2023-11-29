#include <iostream>

constexpr double calculate_e(double epsilon)
{

    auto e = 1.0;
    auto summand = 1.0;

    for (auto k = 1; ; k++)
    {

        summand /= k;
        e += summand;

        if (summand < epsilon)
        {
            return e;
        }

    }
}

constexpr auto result = calculate_e(0.001);

int main()
{
    std::cout << result << std::endl;
}