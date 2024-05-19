#include <random>
#include <iostream>
#include <mutex>
#include <thread>


class PiCalculator
{
public:

    explicit PiCalculator(std::size_t size): m_size(size){}

    void operator()()
    {
        const std::size_t min_size = 1000; 

        const std::size_t max_threads = (m_size + min_size - 1) / min_size;

        const std::size_t hardware = std::thread::hardware_concurrency();

        const std::size_t n_threads = std::min(hardware != 0 ? hardware : 2, max_threads);
        
        {
            std::vector < std::jthread > threads(n_threads-1);
            
                for (auto i = 0; i < std::size(threads); i++)
                {   
                    threads[i] = std::jthread(&PiCalculator::generate_points, this, m_size/n_threads);
                }
        }

        generate_points(m_size - (m_size/n_threads)*(n_threads-1));
    }

    void generate_points(std::size_t size)
    {
        std::random_device device;
        std::mt19937_64 engine(device());
        std::uniform_real_distribution distribution(0.0, 1.0); 
        
        std::size_t counter{0};

        for (std::size_t i = 0; i < size; ++i)
        {
            const auto x = distribution(engine);
            const auto y = distribution(engine);

            if (x*x + y*y < 1.0) 
            {
                counter++;
            }
        }

        std::scoped_lock lock(mutex);
        m_counter += counter;
    }

    double get_pi()
    {
        return (4.0 * m_counter)/m_size;
    }

private:
    std::size_t m_size;
    std::size_t m_counter;
    std::mutex mutex;
};

int main()
{
    std::size_t size {100'000'000};
    PiCalculator picalculator(size);
    picalculator();
    std::cout << picalculator.get_pi();
}