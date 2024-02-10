#include <iostream>
#include <memory>

class Computer
{
public:
    
    virtual ~Computer() = default; // note: polymorphic base class

    [[nodiscard]] virtual std::unique_ptr<Computer> clone() const = 0; // note: virtual copy

    virtual void run() const = 0;

}; // class Computer

class Mobile : public Computer
{
public:

    [[nodiscard]] std::unique_ptr<Computer> clone() const override 
    { 
        return std::make_unique<Mobile>(*this); // note: delete required
    } 

    void run() const override { std::cout << "Mobile" << std::endl; };

}; // class Mobile : public Computer

class Tablet : public Computer
{
public:

    [[nodiscard]] std::unique_ptr<Computer> clone() const override 
    { 
        return std::make_unique<Tablet>(*this); // note: delete required
    } 

    void run() const override { std::cout << "Tablet" << std::endl; };

}; // class Tablet : public Computer

class Laptop : public Computer
{
public:

    [[nodiscard]] std::unique_ptr<Computer> clone() const override 
    { 
        return std::make_unique<Laptop>(*this); // note: delete required
    } 

    void run() const override { std::cout << "Laptop" << std::endl; };

}; // class Laptop : public Computer

class Factory // note: no factories hierarchy, static prototypes and virtual copy
{
public:

    [[nodiscard]] static auto create_mobile() { return mobile_prototype.clone(); }
    [[nodiscard]] static auto create_tablet() { return tablet_prototype.clone(); }
    [[nodiscard]] static auto create_laptop() { return laptop_prototype.clone(); }

private:

    static inline const Mobile mobile_prototype;
    static inline const Tablet tablet_prototype;
    static inline const Laptop laptop_prototype;

}; // struct Factory

int main()
{
    auto mobile = Factory::create_mobile(); 

    mobile->run(); 

    return 0;
}