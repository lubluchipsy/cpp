#include <iostream>

class Fahrenheit_Sensor
{
public:

 double get_temperature() const { return 451.0; } 

};

class Sensor
{
public:

 virtual ~Sensor() = default;

public:

 virtual double get_temperature() const = 0;

}; 

class Adapter : private Fahrenheit_Sensor, public Sensor
{

public:

 double get_temperature() const override 
 {
  return (Fahrenheit_Sensor::get_temperature() - 32.0) * 5.0 / 9.0;
 }

};

int main()
{

 Sensor* new_sensor = new Adapter();

 std::cout << new_sensor->get_temperature() << std::endl;

 delete new_sensor; 

 return 0;
}