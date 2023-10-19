#include <iostream>

template <typename ... Types >

int args_memory(Types ... args)  // using decay conversion
{
	return (sizeof(args)+...);
}

int main()
{
	std::cout << args_memory(12, 2.0, 5, 'a');
}