#include <iostream>

template<typename foo, typename... Types>
void call_function(foo&& f, Types&&... args)
{
    f(std::forward<Types>(args)...);
}

void sum(int a, int b)
{
	std::cout << a+b;
}

int main()
{
    int a = 3;
    int b = 5;
    call_function(sum, a, b);
}

