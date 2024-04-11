#include <iostream>
#include <string>
#include <cassert>

std::string capitalize(std::string const & text)
{
    std::string result;
    bool newWord = true;
    for (auto const ch : text)
    {
        newWord = newWord || std::ispunct(ch) || std::isspace(ch);
        if (std::isalpha(ch))
        {
            if (newWord)
            {
                result.push_back(std::toupper(ch));
                newWord = false;
            }
            else
            result.push_back(std::tolower(ch));
        }
        else result.push_back(ch);
    }
    return result;
}

int main()
{
    assert(capitalize("hEllo, wOrLd!") == "Hello, World!");

    return 0;    
}