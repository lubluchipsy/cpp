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
        std::size_t n_threads = std::thread::hardware_concurrency();
        
        {
            std::vector < std::jthread > threads(n_threads-1);
            
                for (auto i = 0; i < std::size(threads); i++)
                {   
                    threads[i] = std::jthread(&PiCalculator::generate_points, this, m_size/n_threads);
                }
        }

        generate_points(m_size/n_threads);
    }

    void generate_points(std::size_t size)
    {
        std::random_device device;
        std::mt19937_64 engine(device());
        std::uniform_real_distribution distribution(0.0, 1.0); 

        for (std::size_t i = 0; i < size; ++i)
        {
            const auto x = distribution(engine);
            const auto y = distribution(engine);

            if (x*x + y*y < 1.0) 
            {
                std::scoped_lock lock(mutex);
                m_counter++;
            }
        }
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