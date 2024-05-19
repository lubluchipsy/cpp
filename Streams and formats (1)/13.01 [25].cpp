#include <iostream>
#include <vector>
#include <cassert>
#include <sstream>
#include <string>
#include <iomanip>

std::string ints_to_string(const std::vector <int> & nums)
{
    std::ostringstream stream;
    stream.setf(std::ios_base::uppercase);
    stream << std::hex << std::noshowbase << std::setw(2);
    for (auto i:nums)
    {
        stream << i;
    }
    return stream.str();
}

int main()
{
    std::vector <int> numbers {0xBA, 0xAD};
    assert(ints_to_string(numbers) == "BAAD");
    std::cout << ints_to_string(numbers);
    return 0;
}