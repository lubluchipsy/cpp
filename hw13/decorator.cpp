#include <iostream>
#include <string>
#include <memory>

class Computer 
{
public:

    virtual ~Computer() = default; // note: polymorphic base class

    [[nodiscard]] virtual std::string description() const = 0;

}; // class Computer 

struct Mobile : public Computer { [[nodiscard]] std::string description() const override { return "Mobile"; } };
struct Tablet : public Computer { [[nodiscard]] std::string description() const override { return "Tablet"; } };
struct Laptop : public Computer { [[nodiscard]] std::string description() const override { return "Laptop"; } };

class Decorated_Computer : public Computer // note: abstract decorator
{
public:

    explicit Decorated_Computer(std::shared_ptr<Computer> computer): m_computer(std::move(computer))
    {
        if (!m_computer) std::cout << "invalid computer" << std::endl;
    }

    [[nodiscard]] std::string description() const override { return m_computer->description(); }

protected:

    std::shared_ptr<Computer> m_computer;

}; // class Decorated_Computer : public Computer 

class Overclocked_Computer : public Decorated_Computer // note: concrete decorator
{
public:

    explicit Overclocked_Computer(std::shared_ptr<Computer> computer) : Decorated_Computer(std::move(computer)) {}

    [[nodiscard]] std::string description() const override
    { 
        return "Overclocked " + m_computer->description();
    }

}; // class Overclocked_Computer : public Decorated_Computer

int main()
{
    auto mobile = std::make_shared<Mobile>();

    std::cout << mobile->description() << std::endl;

    auto overclocked_mobile = std::make_shared<Overclocked_Computer> (std::move(mobile));

    std::cout << overclocked_mobile->description() << std::endl;

    return 0;
}