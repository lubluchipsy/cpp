#include <iostream>

int main()
{
    auto max = 1;
    auto start = 1;
    for(auto i = 2; i <= 10000; i++)
    {
        auto c = 1;
        auto n = i;
        while (n != 1)
        {
            if (n % 2 == 0)
            {
                n /=2;
            }
            else
            {
                n = 3*n + 1;
            }
            c += 1;
        }
        if (c > max)
        {
            max = c;
            start = i;
        }
    }
    std::cout << "The longest chain has " << max << " members and starts with " << start  ;
}