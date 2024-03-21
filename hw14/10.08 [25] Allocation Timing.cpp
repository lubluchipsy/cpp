#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>
#include <chrono>
#include <vector>
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

void allocation_time(long int size, Timer & timer)
{
	timer.start();
	auto ptr = ::operator new(size);
	::operator delete(ptr);
	timer.stop();
}	

int main()
{
    Timer timer("Memory test");

	std::ofstream out;          
    out.open("allocation_time.txt");     
    if (out.is_open())
	{
		for (long int size = pow(2, 10); size <= pow(2, 30); size *= 4)
		{
			allocation_time(size, timer);

			out << "Allocation of " << size << " bytes took " <<  timer.m_series.back() / 1'000'000.0 << " seconds" << std::endl;
		}
	}
	
	// results in allocation_time.txt

    return 0;
}