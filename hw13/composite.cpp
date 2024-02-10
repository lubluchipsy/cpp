#include <iostream>
#include <vector>
#include <memory>

class Computer
{
public:

    virtual ~Computer() = default; // note: polymorphic base class

    [[nodiscard]] virtual std::size_t cores() const = 0;

}; // class Computer

struct Mobile : public Computer { [[nodiscard]] std::size_t cores() const override { return 1; } };
struct Tablet : public Computer { [[nodiscard]] std::size_t cores() const override { return 2; } };
struct Laptop : public Computer { [[nodiscard]] std::size_t cores() const override { return 3; } };

class Cluster : public Computer // note: composite class of concrete computers
{
public:

    ~Cluster() = default;

    [[nodiscard]] std::size_t cores() const override
    {
        std::size_t total_cores = 0;

        for (std::size_t i = 0; i < m_computers.size(); ++i)
        {
            if (m_computers[i]) total_cores += m_computers[i]->cores();
        }

        return total_cores;
    }

    void add_computer(std::shared_ptr<Computer> computer) { m_computers.push_back(std::move(computer)); }

private:
    
    std::vector < std::shared_ptr<Computer> > m_computers;

}; // class Cluster : public Computer

[[nodiscard]] auto make_cluster(std::size_t n_mobiles, std::size_t n_tablets, std::size_t n_laptops)
{
    auto cluster = std::make_shared<Cluster>();

    for (std::size_t i = 0; i < n_mobiles; ++i) cluster->add_computer(std::make_shared<Mobile>());
    for (std::size_t i = 0; i < n_tablets; ++i) cluster->add_computer(std::make_shared<Tablet>());
    for (std::size_t i = 0; i < n_laptops; ++i) cluster->add_computer(std::make_shared<Laptop>());

    return cluster;
}

int main()
{
    auto super_cluster = std::make_shared<Cluster>();

    for (std::size_t i = 0; i < 4; ++i) super_cluster->add_computer(make_cluster(1, 1, 1));

    std::shared_ptr<Computer> computer = super_cluster;
        
    std::cout << computer->cores() << std::endl;

    return 0;
}