#include <iostream>

constexpr auto is_prime(int p) 
{

	for (auto d = 2; d <= p / 2; ++d)
	{
		if (p % d == 0)
		{
			return false;
		}
	}

	return true;
}

constexpr auto n_prime(int n)
{
    int counter = 0;
    int number = 2;

    while (counter < n)
    {
        if (is_prime(number))
        {
            ++counter;
        }

        ++number;
    }

    return number - 1;
}

constexpr auto result = n_prime(5);

int main()
{
    std::cout << result;
}