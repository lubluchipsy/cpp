#include <iostream>
#include <string>
#include <optional>

class Person
{

public:

    Person(const std::string & surname, const std::string & name,  const std::optional <std::string> & patronymic): name_(name),
                                                                                                                    surname_(surname),
                                                                                                                    patronymic_(patronymic){};

    Person(const std::string & surname, const std::string & name): name_(name),
                                                                   surname_(surname){};

    void get_initials()
    {

        if(patronymic_)
        {
            std::cout << char(toupper(name_[0])) << "."
                      << char(toupper(patronymic_.value()[0])) << "." 
                      << char(toupper(surname_[0]))
                      << surname_.substr(1) << std::endl;
        }

        else
        {
            std::cout << char(toupper(name_[0])) << "."
                      << char(toupper(surname_[0]))
                      << surname_.substr(1) << std::endl;
        }
        
    }

private:

    std::string name_;
    std::string surname_;
    std::optional <std::string> patronymic_;
};


int main()
{
    Person p1("tolstikova", "marina");

    p1.get_initials();

    Person p2("tolstikova", "marina", "sergeevna");

    p2.get_initials();
}