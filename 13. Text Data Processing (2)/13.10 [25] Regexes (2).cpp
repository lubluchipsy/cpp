#include <vector>
#include <iostream>
#include <iterator>
#include <regex>
#include <string>

using namespace std::literals;

[[nodiscard]] std::vector<std::string> search_email_adress(const std::string & data)
{
    std::vector<std::string> emails;
    std::smatch matches; 
    auto pattern = std::regex(R"([-\.\w]+@([\w-]+\.)+[\w-]{2,4})");

    for (auto begin = std::cbegin(data); std::regex_search(begin, std::cend(data), matches, pattern); begin = matches.suffix().first)
    {
        emails.push_back(matches[0]);
    }

    return emails;
}

int main()
{
    const std::string text = R"(test@mail.com, f()ji)@gmail.com ae32-f.@mail.ru sfsv@sn23. )";
    std::vector<std::string> matches = search_email_adress(text);
    for (auto match:matches)
    {
        std::cout << match << ' '; //matches = ["test@mail.com", "ae32-f.@mail.ru "]
    }
    std::cout << std::endl;
    return 0;
}