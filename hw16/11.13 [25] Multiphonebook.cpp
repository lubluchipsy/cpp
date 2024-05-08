#include <boost/multi_index_container.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/random_access_index.hpp>
#include <string>
#include <boost/bimap.hpp>
#include <cassert>
#include <iostream>

struct Person
{
    std::string phone_number;
    std::string name;
    std::string surname;
};

using Persons = boost::multi_index::multi_index_container
<
    Person,
    boost::multi_index::indexed_by
    <
        boost::multi_index::ordered_non_unique <
            boost::multi_index::tag < struct PersonsBySurname >,
            boost::multi_index::member < Person, decltype(Person::surname), &Person::surname > >,
        boost::multi_index::random_access <
            boost::multi_index::tag<struct PersonsRandomAccess> >,
        boost::multi_index::hashed_unique <
            boost::multi_index::tag<struct PersonsHashed>,
            boost::multi_index::member<Person, decltype(Person::phone_number), &Person::phone_number> >
    >
>;  

int main()
{
    Persons persons;
    
    persons.insert({"88005553535", "Sergey", "Sergeev"});
    persons.insert({"89001234567", "Ivan", "Ivanov"});
    persons.insert({"88009876534", "Dmitriy", "Dmitriev"});
    persons.insert({"89172345678", "Roman", "Romanov"});
    
  
    auto & personsByName = persons.get<PersonsBySurname>();
    auto & personsRandomAccess = persons.get<PersonsRandomAccess>();
    auto & personsHashed = persons.get<PersonsHashed>();

    using namespace std::literals::string_literals;

    assert(personsRandomAccess[0].name == "Sergey");

    std::cout << personsHashed.find("89001234567"s)->name << std::endl;

    for(auto i = personsByName.begin(); i != personsByName.end(); i++)
    {
        std::cout << i->name << " ";
    }
    std::cout << std::endl;

}   