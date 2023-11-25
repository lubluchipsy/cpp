#include <iostream>
#include <variant>
#include <math.h>

using Roots = std::variant <std::monostate, std::pair < double, double >, double>;
using Pair = std::pair < double, double >;


Roots solve(double a, double b, double c)
{
    double D = b*b - 4*a*c;

    if (D < 0)
    {
        return std::monostate();
    }

    if (D == 0.0)
    {
        return (- b / (2*a));
    }

    if (D > 0)
    {
        return std::make_pair((-b + sqrt(D))/ (2*a), (-b - sqrt(D))/ (2*a));
    }
}


void get_roots(const Roots & roots)
{
    if (std::holds_alternative < std::monostate > (roots))
    {
        std::cout << "There are no solutions." << std::endl;
    } 

    if (std::holds_alternative < Pair > (roots))
    {
        Pair pair = std::get < Pair > (roots);
        std::cout << "Roots: " << pair.first << ", " << pair.second << std::endl;
    } 

    if (std::holds_alternative < double > (roots))
    {
        std::cout << "Root: " << std::get < double > (roots) << std::endl;
    }
}


int main()
{
    get_roots(solve(1, -2, 1));

    get_roots(solve(2, -5, 2));

    get_roots(solve(2, 1, 1));
}