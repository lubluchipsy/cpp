#include <iostream>
#include <vector>
#include <memory>

class Observer 
{
public:

    virtual ~Observer() = default; // note: polymorphic base class

    virtual void update(double temperature) const = 0;

}; // class Observer 

class Computer 
{
public:

    ~Computer() = default;

    void set_temperature(double temperature) 
    {
        m_temperature = temperature;
        notify_all();
    }

    void notify_all() const 
    { 
        for (std::size_t i = 0; i < m_observers.size(); ++i)
        {
            if (m_observers[i]) m_observers[i]->update(m_temperature);
        }
    }

    void add_observer(std::unique_ptr<Observer> observer) { m_observers.push_back(std::move(observer)); }

private:

    double m_temperature = 0.0; 
    std::vector < std::unique_ptr<Observer> > m_observers;

}; // class Computer 

class Display_1 : public Observer 
{
public:

    void update(double temperature) const override
    {
        std::cout << "Display 1: temperature = " << temperature << std::endl;
    }

}; // class Display_1 : public Observer 

class Display_2 : public Observer
{
public:

    void update(double temperature) const override
    {
        std::cout << "Display 2: temperature = " << temperature << std::endl;
    }

}; // class Display_2 : public Observer 

int main() 
{
    Computer computer;

    computer.add_observer(std::make_unique<Display_1>());
    computer.add_observer(std::make_unique<Display_2>());

    computer.set_temperature(25.5);
    computer.set_temperature(24.8);

    return 0;
}