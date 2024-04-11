#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ranges>

std::string find_lcs(std::string & s1, std::string & s2)
{
    const std::size_t n = s1.size();
    const std::size_t m = s2.size();

    std::vector<std::vector<int>> table((n+1), std::vector<int>(m+1));

    for (auto i = 0; i < n+1; i++)
    {
        for (auto j = 0; j < m+1; j++)
        {
            if (i == 0 || j == 0)
            {
                table[i][j] = 0;
            }
            else if (s1[i-1] == s2[j-1])
            {
                table[i][j] = table[i-1][j-1] + 1;
            }
            else
            {
                table[i][j] = (table[i-1][j] >= table[i][j-1]) ? table[i-1][j] : table[i][j-1];
            } 
        } 
    }

    std::string lcs;
    auto i = n;
    auto j = m;

    while (i > 0 && j > 0)
    {
        if (s1[i-1] == s2[j-1])
        {
            lcs.push_back(s1[i-1]);
            i--;
            j--;
        }
        else
        {
            if (table[i-1][j] > table[i][j-1])
            {
                i--;
            }
            else
            {
                j--;
            }
        }
    }
    std::ranges::reverse(lcs);
    return lcs;
}


int main()
{
    std::string s1 = "AGGTAB";
    std::string s2 = "GXTXAYB";

    std::cout << find_lcs(s1, s2) << std::endl;

    return 0;
}