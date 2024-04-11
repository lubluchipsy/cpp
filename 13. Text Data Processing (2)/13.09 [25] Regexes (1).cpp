#include <vector>
#include <iostream>
#include <iterator>
#include <regex>
#include <string>

using namespace std::literals;

[[nodiscard]] std::vector<std::string> search_car_number(const std::string & data)
{
    std::vector<std::string> numbers;
    std::smatch matches; 
    auto pattern = std::regex(R"([[:alpha:]]\d{3}[[:alpha:]]{2}\d{3})");

    for (auto begin = std::cbegin(data); std::regex_search(begin, std::cend(data), matches, pattern); begin = matches.suffix().first)
    {
        numbers.push_back(matches[0]);
    }

    return numbers;
}

int main()
{
    const std::string text = R"(fsfv 2ds,A087BC777 WO a087Bc777'/a a08bC777;s 087BC777 ks298sn02;jo)";
    std::vector<std::string> matches = search_car_number(text);
    for (auto match:matches)
    {
        std::cout << match << ' '; //matches = ["A087BC777", "a087Bc777"]
    }
    std::cout << std::endl;
    return 0;
}