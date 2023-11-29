#include <iostream>

template < int N, int K >
struct BinomialCoefficient 
{
    static const int value = BinomialCoefficient < N-1, K-1 > ::value + BinomialCoefficient < N-1, K > ::value;
};

template <>
struct BinomialCoefficient < 0, 0 > 
{
    static const int value = 1;
};


template < int N >
struct BinomialCoefficient < N, 0 > 
{
    static const int value = 1;
};

template < int N >
struct BinomialCoefficient < N, N > 
{
    static const int value = 1;
};

template < auto n, auto k > const auto bin_coeff_v = BinomialCoefficient < n, k > ::value;

int main()
{
    std::cout << bin_coeff_v < 5, 3 > << std::endl;
}