#include <iostream>

struct Printer     
{
    Printer() 
    {
        std::cout << "Hello, world!" << std::endl;
    }
};

Printer Printer;  // outputting string with struct constuctor


const int printer = (std::cout << "Hello, world!" << std::endl, 0);  //outputting string with a const variable 

int printer_foo()
{
    std::cout << "Hello, world!";
    return 0;
}

int print = printer_foo(); // outputting string using function


int main()
{
    return 0;
}