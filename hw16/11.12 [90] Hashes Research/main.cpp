#include "hashes_research.hpp"
#include <fstream>


int main()
{
    std::vector <unsigned int> RS;     RS.reserve(20);
    std::vector <unsigned int> JS;     JS.reserve(20);
    std::vector <unsigned int> ELF;   ELF.reserve(20);
    std::vector <unsigned int> PJW;   PJW.reserve(20);
    std::vector <unsigned int> BKDR; BKDR.reserve(20);
    std::vector <unsigned int> SDBM; SDBM.reserve(20);
    std::vector <unsigned int> DJB;   DJB.reserve(20);
    std::vector <unsigned int> DEK;   DEK.reserve(20);
    std::vector <unsigned int> AP;     AP.reserve(20);

    for (auto number = 100000; number < 2000001; number += 100000)
    {
        std::unordered_set <std::string> strings = random_strings(10, number);

        std::unordered_set <unsigned int> RShashes;
        std::unordered_set <unsigned int> JShashes;
        std::unordered_set <unsigned int> ELFhashes;
        std::unordered_set <unsigned int> PJWhashes;
        std::unordered_set <unsigned int> BKDRhashes;
        std::unordered_set <unsigned int> SDBMhashes;
        std::unordered_set <unsigned int> DJBhashes;
        std::unordered_set <unsigned int> DEKhashes;
        std::unordered_set <unsigned int> APhashes;

        for(auto str : strings)
        {
            const char * c = str.c_str();

            RShashes  .insert(RSHash  (c, 10));
            JShashes  .insert(JSHash  (c, 10));
            ELFhashes .insert(ELFHash (c, 10));
            PJWhashes .insert(PJWHash (c, 10));
            BKDRhashes.insert(BKDRHash(c, 10));
            SDBMhashes.insert(SDBMHash(c, 10));
            DJBhashes .insert(DJBHash (c, 10));
            DEKhashes .insert(DEKHash (c, 10));
            APhashes  .insert(APHash  (c, 10));
        }

        RS.  push_back(number - std::size(RShashes  ));
        JS.  push_back(number - std::size(JShashes  ));
        ELF. push_back(number - std::size(ELFhashes ));
        PJW. push_back(number - std::size(PJWhashes ));
        BKDR.push_back(number - std::size(BKDRhashes));
        SDBM.push_back(number - std::size(SDBMhashes));
        DJB. push_back(number - std::size(DJBhashes ));
        DEK. push_back(number - std::size(DEKhashes ));
        AP.  push_back(number - std::size(APhashes  ));
    }  

    std::ofstream out;          // поток для записи
    out.open("collisions.txt");      // открываем файл для записи
    if (out.is_open())
    {
        for (auto i : RS)
        {
            out << i << " ";
        }
        out << std::endl;

        for (auto i : JS)
        {
            out << i << " ";
        }
        out << std::endl;

        for (auto i : ELF)
        {
            out << i << " ";
        }
        out << std::endl;

        for (auto i : PJW)
        {
            out << i << " ";
        }
        out << std::endl;

        for (auto i : BKDR)
        {
            out << i << " ";
        }
        out << std::endl;

        for (auto i : SDBM)
        {
            out << i << " ";
        }
        out << std::endl;

        for (auto i : DJB)
        {
            out << i << " ";
        }
        out << std::endl;

        for (auto i : DEK)
        {
            out << i << " ";
        }
        out << std::endl;

        for (auto i : AP)
        {
            out << i << " ";
        }
        out << std::endl;
    }
    out.close(); 
    
    std::cout << "File has been written" << std::endl;

    return 0;
}