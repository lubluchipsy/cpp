/*
Function can be overrided with a different return type
if the type returned by the overridden function 
is substitutable (sub-class) for the type of the base function.
*/


#include <iostream>


class Gun
{
public:
    virtual void shoot()
    {
        std::cout << "Bang!" << std::endl;
    }
};


class Machine_gun : public Gun
{
public:
    void shoot() override
    {
        std::cout << "Bang! Bang! Bang!" << std::endl;
    }
};


class Gun_factory
{
public:
    virtual Gun* produce()
    {
        std::cout << "Gun is produced." << std::endl;
        return new Gun;
    }
};


class Machine_gun_factory : public Gun_factory
{
public:
    Machine_gun* produce() override
    {
        std::cout << "Machine gun is produced." << std::endl;
        return new Machine_gun;
    }
};


int main()
{
    Machine_gun_factory mgf;
    Gun_factory gf;

    Gun* new_gun = gf.produce();
    new_gun->shoot();

    Machine_gun* new_machine_gun = mgf.produce();
    new_machine_gun->shoot();

    return 0;
}

