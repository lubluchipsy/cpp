#include <iostream>
#include <string>

std::string reverse(std::string  & s)
{
    std::string reversed;
    for (auto i = s.end(); i != s.begin() - 1; i--)
    {
        reversed.push_back(*i);
    }

    return reversed;
}

std::string find_lcs(std::string & s1, std::string & s2)
{
    std::size_t n = s1.size();
    std::size_t m = s2.size();

    int table[n+1][m+1];

    for (auto i = 0; i < n+1; i++)
    {
        for (auto j = 0; j < m+1; j++)
        {
            if (i == 0 || j == 0)
            {
                table[i][j] = 0;
            }
            if (s1[i-1] == s2[j-1])
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

    
    return reverse(lcs);
}


int main()
{
    std::string s1 = "AGGTAB";
    std::string s2 = "GXTXAYB";

    std::cout << find_lcs(s1, s2) << std::endl;

    return 0;
}