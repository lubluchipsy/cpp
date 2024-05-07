#include <thread>
#include <math.h>
#include <random>
#include <iostream>
#include <cassert>

std::size_t generate_points(std::size_t size)
{
    std::random_device device;
	std::mt19937_64 engine(device());
	std::uniform_real_distribution distribution(0.0, 1.0); 

	std::size_t circle = 0;
	for (std::size_t i = 0; i < size; ++i)
	{
		const auto x = distribution(engine);
		const auto y = distribution(engine);

		if (x*x + y*y < 1.0) ++circle;
	}

    return circle;
}

class Counter
{
public:
    explicit Counter(std::size_t size, std::size_t & count): m_size(size), m_count(count){}

    void operator()() const noexcept
	{
		try
		{
			m_count = generate_points(m_size);
		}
		catch(const std::exception &) {}
	}

private:
    const std::size_t m_size;
    std::size_t & m_count;
};

double calculate_pi(std::size_t size)
{
    const std::size_t n_threads = std::thread::hardware_concurrency();

    std::vector < std::size_t > results(n_threads, 0);

    {
        std::vector < std::jthread > threads(n_threads-1);
        
        for (auto i = 0; i < std::size(threads); i++)
        {   
            threads[i] = std::jthread(Counter(size/n_threads, results[i]));
        }
    }

    Counter(size/n_threads, results[std::size(results)-1])();

    double sum = std::accumulate(results.begin(), results.end(), 0);

    return 4 * sum / size;
}

int main()
{
    std::cout << calculate_pi(10000000);
}