#include <iostream>
#include <string>


class Person
{
public:
    std::string m_name;
    int m_age;
    int m_height;
};


class Builder: public Person
{
public:

    auto get() const {return m_person;}

    Builder name(std::string name)
    {
        m_person.m_name = name;
        return *this;
    }

    Builder age(int age)
    {
        m_person.m_age = age;
        return *this;
    }

    Builder height(int height)
    {
        m_person.m_height = height;
        return *this;
    }

private:

    Person m_person;
};


int main()
{
    Builder builder;

    Person p = builder.name("Ivan").age(26).height(180).get();

    std::cout << p.m_name << " " << p.m_age << " " << p.m_height << std::endl;
}