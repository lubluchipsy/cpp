#include <iostream>
#include <memory>

class Computer
{
public:

    virtual ~Computer() = default; // note: polymorphic base class

    virtual void run() const = 0;
    
}; // class Computer

struct Mobile : public Computer { void run() const override { std::cout << "Mobile" << std::endl; }; };
struct Tablet : public Computer { void run() const override { std::cout << "Tablet" << std::endl; }; };
struct Laptop : public Computer { void run() const override { std::cout << "Laptop" << std::endl; }; };

template < typename T > std::shared_ptr<Computer> create() // note: factory function, consider enumeration
{
    return std::make_shared<T>(); // note: delete required, consider type traits to verify type T is correct
}

class Server : public Computer
{
public:

    struct Factory // note: factory methods
    {
        static std::shared_ptr<Computer> create_v1() { return std::make_shared<Server>(1); } // note: delete required
        static std::shared_ptr<Computer> create_v2() { return std::make_shared<Server>(2); } // note: delete required
        static std::shared_ptr<Computer> create_v3() { return std::make_shared<Server>(3); } // note: delete required

    }; // struct Factory

    void run() const override { std::cout << "Server v" << m_version << std::endl; };

private:

    explicit Server(int version) : m_version(version) {}; // note: use factory methods

    int m_version = 0;

}; // class Server : public Computer

class Factory
{
public:

    virtual ~Factory() = default; // note: polymorphic base class

    [[nodiscard]] virtual std::shared_ptr<Computer> create() const = 0;
    
}; // class Factory

class Factory_Mobile : public Factory
{
public:

    [[nodiscard]] std::shared_ptr<Computer> create() const override
    { 
        return std::make_shared<Mobile>(); // note: delete required
    } 

}; // class Factory_Mobile : public Factory

class Factory_Tablet : public Factory
{
public:

    [[nodiscard]] std::shared_ptr<Computer> create() const override
    { 
        return std::make_shared<Tablet>(); // note: delete required
    } 

}; // class Factory_Tablet : public Factory

class Factory_Laptop : public Factory
{
public:

    [[nodiscard]] std::shared_ptr<Computer> create() const override
    { 
        return std::make_shared<Laptop>(); // note: delete required
    } 

}; // class Factory_Laptop : public Factory

int main()
{
    auto mobile = create < Mobile > (); 

    mobile->run();

    auto server = Server::Factory::create_v1(); 

    server->run(); 

    std::shared_ptr<Factory> factory_laptop = std::make_shared<Factory_Laptop>(); // note: delete required

    auto laptop = factory_laptop->create(); 

    laptop->run(); 

    return 0;
}