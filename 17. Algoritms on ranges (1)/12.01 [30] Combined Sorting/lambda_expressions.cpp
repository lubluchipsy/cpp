#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <utility>
#include <vector>


template <class Less>
void insertion_sort(std::vector < int > & v, std::size_t l, std::size_t r, Less less) // note: O(N^2) complexity 
{
	for (auto i = l + 1; i < r; ++i)
	{
		for (auto j = i; j > l; --j)
		{
			if (less(v[j], v[j-1])) // note: sort in ascending order
			{
				std::swap(v[j], v[j - 1]);
			}
		}
	}
}

template <class Less>
void merge_sort(std::vector < int > & v, std::size_t l, std::size_t m, std::size_t r, Less less)
{
	const auto begin = l, end = m;

	std::vector < int > t(r - l, 0); // note: one additional container instead of two

	for (auto & e : t) e = v[((l < end && ((m < r && !less(v[m], v[l])) || (m == r))) ? l++ : m++)];

	for (std::size_t i = 0; auto e : t) v[begin + (i++)] = e;
}

template <class Less>
void merge_sort(std::vector < int > & v, std::size_t l, std::size_t r, Less less) // note: O(N*log(N)) complexity (amortized)
{
	if (static const std::size_t block = 64; r - l <= block)
	{
		insertion_sort(v, l, r, less); // good: double nested loop instead of recursive calls
	}
	else
	{
		const auto m = std::midpoint(l, r); 
		
		merge_sort(v, l, m   , less);
		merge_sort(v,    m, r, less);
		merge_sort(v, l, m, r, less);
	}
}

class Comp
{
public:
    bool operator()(const int lhs, const int rhs) const noexcept {return lhs > rhs;}
};

int main()
{
	const std::size_t n = 10;
	std::vector < int > vector(n, 0);
	std::iota(std::begin(vector), std::end(vector), 1); // vector = 1 2 3 4 5 6 7 8 9 10

	merge_sort(vector, 0, n, [](const int lhs, const int rhs){return lhs > rhs;});

	for (const auto element:vector) std::cout << element << ' '; //output: 10 9 8 7 6 5 4 3 2 1
    std::cout << std::endl;

	return 0;
}