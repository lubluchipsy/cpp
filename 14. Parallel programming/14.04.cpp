#include <cassert>
#include <cmath>
#include <concepts>
#include <future>
#include <iterator>
#include <numeric>
#include <ranges>
#include <thread>
#include <utility>
#include <vector>
#include <chrono>
#include <iostream>

class Timer
{
public:

	using clock_t = std::chrono::steady_clock;

	explicit Timer(std::string name) : m_name(std::move(name)), m_is_running(false)
	{
		std::cout << "Timer " << m_name << " launched ... " << std::endl;
	}

	void start()
	{
		if (m_is_running != false)
		{
			throw std::logic_error("Timer is already running.");
		}

		m_begin = clock_t::now();
		m_is_running = true;
	}

	void stop()
	{
		if (m_is_running != true)
		{
			throw std::logic_error("Timer is not running.");
		}

		m_is_running = false;
		m_series.push_back(std::chrono::duration_cast<std::chrono::microseconds>(clock_t::now() - m_begin).count());
	}

	auto result()
	{
		if (m_series.empty())
		{
			return 0.0;
		}

		auto sum = 0.0;
		for (auto time : m_series)
		{
			sum += time;
		}

		return sum / m_series.size() / 1'000'000.0;
	}

	std::vector<long long> m_series;

private:

	const std::string m_name;

	clock_t::time_point m_begin;

	bool m_is_running;

}; // class Timer

//  ================================================================================================

template < std::ranges::view V > class Block
{
public:

    explicit Block(V view) noexcept : m_view(view) {}

	[[nodiscard]] auto operator()() const
	{
		return std::reduce(std::ranges::cbegin(m_view), std::ranges::cend(m_view), 0.0, [](double sum, double n){return sum + 5.23*std::cos(2.5385*std::sin(n));});
	}

private:

    const V m_view;

}; // template < std::ranges::view V > class Block

//  ================================================================================================

template < std::ranges::view V, typename T > T reduce(V view, T sum, std::size_t n_threads)
{
	const auto begin = std::ranges::cbegin(view), end = std::ranges::cend(view);

	std::size_t size = std::distance(begin, end);

	if (!size) return sum;

	size /= n_threads;

	std::vector < std::pair < std::future < T > , std::jthread > > results(n_threads - 1);

	auto first = begin;

	for (auto & result : results)
	{
		const auto last = std::next(first, size);

		std::packaged_task task { Block(std::ranges::subrange(first, last)) };

		result.first = task.get_future(); result.second = std::jthread(std::move(task));

		first = last;
	}

	sum += Block(std::ranges::subrange(first, end))();

	for (auto & result : results) sum += result.first.get();

	return sum;
}

//  ================================================================================================

int main()
{
	constexpr std::size_t size = 1'000'000;

	std::vector < int > vector(size, 0);

	std::iota(std::begin(vector), std::end(vector), 1);

	Timer timer("threads");

	for (auto n_threads = 2; n_threads < 20; n_threads++)
	{
		timer.start();
		{reduce(std::views::all(vector), 0.0, n_threads);}
		timer.stop();
	}

	std::cout << "[";
	for (auto result : timer.m_series)
	{
		std::cout << result/1000000.0 << ", ";
	}
	std::cout << "]" << std::endl;

	return 0;
}