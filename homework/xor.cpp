#include <iostream>

int main()
{
    int a{};
    int b{};
    std::cout << "Input a\n";
    std::cin >> a;
    std::cout << "Input b\n";
    std::cin >> b;
	a = static_cast < bool > (a);
	b = static_cast < bool > (b);
    auto result = (a || b) - (a && b );
    std::cout << "a xor b = " << result;
}