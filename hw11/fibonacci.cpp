#include <iostream>

template < auto N > 
struct Fibonacci
{

	static const auto value = N + Fibonacci < N - 1 > ::value;

}; 

template < > 
struct Fibonacci < 1 >
{

	static const auto value = 1;

}; 

template < auto N > const auto fib_v = Fibonacci < N > ::value;

int main()
{
	std::cout << fib_v < 4 > << std::endl;
}