#include <iostream>
#include <vector>
#include <cassert>
#include <sstream>
#include <string>

std::string ints_to_string(std::vector <int> nums)
{
    std::ostringstream stream;
    stream.setf(std::ios_base::uppercase);
    stream << std::hex;
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
    return 0;
}