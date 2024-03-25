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


struct Printer
{
    void operator()(const std::monostate & monostate) const
    {
        std::cout << "There are no solutions." << std::endl;
    }
    void operator()(const double root) const
    {
        std::cout << "Root: " << root << std::endl;
    }
    void operator()(const Pair & roots) const
    {
        std::cout << "Roots: " << roots.first << ", " << roots.second << std::endl;
    }
};


int main()
{
    std::visit(Printer{}, solve(1, -2, 1));

    std::visit(Printer{}, solve(2, -5, 2));

    std::visit(Printer{}, solve(2, 1, 1));

    return 0;
}