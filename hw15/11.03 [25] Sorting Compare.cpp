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
#include <fstream>

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
    const std::size_t size = 1000000;

    std::random_device rd;   // non-deterministic generator
    std::mt19937 gen(rd());  // to seed mersenne twister.
    std::uniform_int_distribution<> dist(0, size); 

    std::vector <int> vector;
    vector.reserve(size);

    std::array <int, size> array;

    std::deque <int> deque;

    std::list <int> list;

    std::forward_list <int> f_list;

    for (auto i = 0; i < size; i++)
    {
        auto element{dist(gen)};

        vector.push_back(element);
        array.at(i) = element;
        deque.push_back(element);
        list.push_back(element);
        f_list.push_front(element);
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

    std::ofstream out;          // поток для записи
    out.open("11.03.txt");      // открываем файл для записи
    if (out.is_open())
    {
    out << "Array: " << timer.m_series[0] << " mks" << std::endl;
    out << "Vector: " << timer.m_series[1]<< " mks" << std::endl;
    out << "Deque: " << timer.m_series[2] << " mks" << std::endl;
    out << "List: " << timer.m_series[3] << " mks" << std::endl;
    out << "Forward list: " << timer.m_series[4] << " mks" << std::endl;
    }

    assert(timer.m_series[0] < timer.m_series[1] &&
           timer.m_series[1] < timer.m_series[2] && 
           timer.m_series[2] < timer.m_series[3] &&
           timer.m_series[2] < timer.m_series[4]);
    
    return 0;
}


