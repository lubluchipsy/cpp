#include <iostream>
#include <string>


class Person
{
public:
    std::string m_name;
    int m_age;
    int m_height;
};


class Builder
{
public:

    explicit Builder()
    {
        m_person = new Person;
    }

    virtual ~Builder() = default;

    auto person() const {return m_person;}

    auto get() const {return * m_person;}

    virtual Builder name(std::string name)
    {
        person()->m_name = name;
        return *this;
    }

    virtual Builder age(int age)
    {
        person()->m_age = age;
        return *this;
    }

    virtual Builder height(int height)
    {
        person()->m_height = height;
        return *this;
    }

private:

    Person * m_person;
};


int main()
{
    Builder builder;

    Person p = builder
    .name("Ivan")
    .age(26)
    .height(180)
    .get();

    std::cout << p.m_name << " " << p.m_age << " " << p.m_height << std::endl;
}