#include <iostream>
#include <vector>
#include <array>
#include <deque>
#include <list>
#include <forward_list>
#include <chrono>
#include <random>
#include <algorithm>
#include <cassert>

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


int main()
{
    std::random_device rd;   // non-deterministic generator
    std::mt19937 gen(rd());  // to seed mersenne twister.
    std::uniform_int_distribution<> dist(0,1000000); // distribute results between 1 and 6 inclusive.

    std::vector <int> vector;
    for (auto i = 0; i < 1000000; i++)
    {
        vector.push_back(dist(gen));
    }

    std::array <int, 1000000> array;
    for (auto i = 0; i < 1000000; i++)
    {
        array.at(i) = dist(gen);
    }

    std::deque <int> deque;
    for (auto i = 0; i < 1000000; i++)
    {
        deque.push_back(dist(gen));
    }

    std::list <int> list;
    for (auto i = 0; i < 1000000; i++)
    {
        list.push_back(dist(gen));
    }

    std::forward_list <int> f_list;
    for (auto i = 0; i < 1000000; i++)
    {
        f_list.push_front(dist(gen));
    }

    Timer timer("sorting");

    timer.start();
    std::sort(array.begin(), array.end());
    timer.stop();

    timer.start();
    std::sort(vector.begin(), vector.end());
    timer.stop();

    timer.start();
    std::sort(deque.begin(), deque.end());
    timer.stop();

    timer.start();
    list.sort();
    timer.stop();

    timer.start();
    f_list.sort();
    timer.stop();

    std::cout << "Array: " << timer.m_series[0] << std::endl;
    std::cout << "Vector: " << timer.m_series[1] << std::endl;
    std::cout << "Deque: " << timer.m_series[2] << std::endl;
    std::cout << "List: " << timer.m_series[3] << std::endl;
    std::cout << "Forward list: " << timer.m_series[4] << std::endl;

    assert(timer.m_series[0] < timer.m_series[1] &&
           timer.m_series[1] < timer.m_series[2] && 
           timer.m_series[2] < timer.m_series[3] &&
           timer.m_series[2] < timer.m_series[4]);
    
    return 0;
}


