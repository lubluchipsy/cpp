#include <iostream>

int main()
{
    char ch{};
    std::cin >> ch;
    switch(ch)
    {
        case '0' ... '9':
            std::cout << "Десятичная цифра";
            break;
        case '*':
        case '+':
        case '-':
        case '/':
            std::cout << "Арифметический оператор";
            break;
        case '(':
        case ')':
            std::cout << "Круглая скобка";
            break;
        default:
            std::cout << "Остальные символы";
            break;
    }
}