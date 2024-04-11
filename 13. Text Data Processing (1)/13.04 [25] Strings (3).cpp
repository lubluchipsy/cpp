#include <iostream>
#include <string>
#include <cassert>
#include <vector>

template <typename Iter>
std::string join_strings(Iter begin, Iter end, const std::string & separator)
{
    if (begin == end) return std::string{};
    std::string result = *begin;
    ++begin;
    for (; begin != end; ++begin) 
    {
        result += separator;
        result += *begin;
    }
    return result;
}

template <typename C>
std::string join_strings(C const & c, const std::string & separator)
{
    if (c.size() == 0) return std::string{};
    return join_strings(std::begin(c), std::end(c), separator);
}

int main()
{
    using namespace std::string_literals;
    std::vector<std::string> v1{ "this","is","an","example" };
    std::vector<std::string> v2{ "example" };
    std::vector<std::string> v3{ };
    assert(join_strings(v1, " ") == "this is an example"s);
    assert(join_strings(v2, " ") == "example"s);
    assert(join_strings(v3, " ") == ""s);

    return 0;
}