#include <iostream>

int main()
{
    const auto maxnumber = 1000;
    for (auto number = 100; number < 1000; number++) 
    {
        auto third_digit = number % 10;
        auto second_digit = (number / 10) % 10; 
        auto first_digit = number / 100;
        if ((first_digit*first_digit*first_digit + second_digit*second_digit*second_digit + third_digit*third_digit*third_digit) == number)
            {
                std::cout << number <<" \n";
            }
    }     
}