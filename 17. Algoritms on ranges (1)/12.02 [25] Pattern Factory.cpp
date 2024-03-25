#include <functional>
#include <iostream>
#include <unordered_map>
#include <string>


class Fruit
{
public:

    class Factory
    {
    public:

        [[nodiscard]] Fruit * create(std::string name)
        {
            return instructions[name]();
        }

    private:

        std::unordered_map < std::string, std::function<Fruit * ()> > instructions = 
        {
            {"lemon", [](){return new Fruit("yellow", "sour");}},
            {"apple", [](){return new Fruit("red", "sweet");}},
            {"orange", [](){return new Fruit("orange", "sweet and sour");}}
        };

    }; //class Factory

    void look() const
    {
        std::cout << "Looks " << m_color << std::endl;
    }

    void bite() const
    {
        std::cout << "Tastes " << m_taste << std::endl;
    }

private:

    const std::string m_color;
    const std::string m_taste;
    explicit Fruit(std::string color, std::string taste): m_color(color), m_taste(taste){};

}; // class Fruit 


int main()
{
    const Fruit * const lemon = Fruit::Factory().create("lemon");
    lemon->look();
    lemon->bite();

    return 0;
}


