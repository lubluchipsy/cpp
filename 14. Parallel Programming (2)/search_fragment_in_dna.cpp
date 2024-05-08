#include <random>
#include <iostream>
#include <mutex>
#include <thread>
#include <algorithm>
#include <vector>
#include <ranges>

class DnaSearch
{
public:
    DnaSearch(std::string_view dna, std::string fragment): m_dna(dna), m_fragment(fragment){};

    void operator()()
    {
        std::size_t size {std::size(m_dna)};
        std::size_t min_size {100};

        if (size < min_size)
        {
            find_fragment(m_dna); 
        }
        else
        {
            std::size_t hardware = std::thread::hardware_concurrency();
            std::size_t n_threads = std::min((size + min_size - 1) / min_size, hardware);

            auto begin = std::ranges::cbegin(m_dna), end = std::ranges::cend(m_dna);
            size /= n_threads;
            auto first = begin;

            {
                std::vector <std::jthread> threads(n_threads-1);
                std::size_t m {std::size(m_fragment)};

                for (std::size_t i = 0; i < std::size(threads); ++i)
                {
                    const auto last = std::next(first, size + m);

                    threads[i] = std::jthread(&DnaSearch::find_fragment, this, std::string_view(first, last));

                    first = last;
                }

                find_fragment(std::string_view(first, end));
            }
        }
    }

    void find_fragment(std::string_view view)
    {
        std::size_t pos = m_dna.find(m_fragment, 0);
            while (pos != std::string_view::npos)
            {
                {
                    std::scoped_lock lock(m);
                    m_results.push_back(&m_dna[pos]);
                }
                pos = m_dna.find(m_fragment, pos + 1);
            }
    }

    std::vector <const char *> & results()
    {
        return m_results;
    }

private:
    std::string_view m_dna;
    std::string m_fragment;
    std::vector <const char *> m_results;
    std::mutex m;
};

int main()
{
    std::size_t size{1000};
    std::string dna;
    dna.reserve(size);

    const std::string symbols{"AGTC"};

    std::random_device device;
    std::mt19937_64 engine(device());
    std::uniform_int_distribution<> distribution(0, std::size(symbols) - 1); 

    for (std::size_t i = 0; i < size; ++i)
    {
        dna.push_back(symbols[distribution(engine)]);
    }

    std::cout << dna << std::endl;

    std::string fragment("AGC");

    DnaSearch dna_search(std::string_view(dna), fragment);
    dna_search();
    auto results = dna_search.results();

    std::cout << results.size() << std::endl;

    for (auto pointer : results)
    {
        for (auto i = 0; i < std::size(fragment); i++)
        {
            std::cout << *(pointer+i);
        }
        std::cout << " ";
    }
    std::cout << std::endl;

}