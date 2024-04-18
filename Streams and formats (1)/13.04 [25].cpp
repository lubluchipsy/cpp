#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <stdexcept>

using namespace std::literals;

void remove_empty_lines(std::string file)
{
    auto empty = std::regex(R"([[:space:]]*)");
    {
        std::fstream filein(file, std::ios::in);
        if (!filein.is_open())
            throw std::runtime_error("cannot open input file");

        std::fstream resultout("result.txt", std::ios::out);
        if (!resultout.is_open())
            throw std::runtime_error("cannot create temporary file");

        std::string line;

        while(getline(filein, line, '\n'))
        {
            if (!std::regex_match(line, empty))
            {
                resultout << line << '\n';
            }
        }
    }
    remove(file.c_str());
    rename("result.txt", file.c_str());
}

int main()
{
    remove_empty_lines("test.txt");
    return 0;
}