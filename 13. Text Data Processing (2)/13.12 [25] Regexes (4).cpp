#include <iostream>
#include <iterator>
#include <regex>
#include <string>
#include <cassert>
#include <string_view>

std::string transform_date(std::string_view text)
{
    auto rx = std::regex{ R"(([0-1][0-9])(\/)([0-3][0-9])(\/)(\d{4}))" };
    return std::regex_replace(text.data(), rx, R"($3.$1.$5)");
}
int main()
{
    using namespace std::string_literals;
    assert(transform_date("today is 12/01/2017!"sv) == "today is 01.12.2017!"sv);
    return 0;
}