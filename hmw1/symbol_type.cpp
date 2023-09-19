#include <iostream>

int main()
{
    char ch{};
    std::cin >> ch;
    switch(ch)
    {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            std::cout << "Digit";
            break;
        case '*':
        case '+':
        case '-':
        case '/':
            std::cout << "Arithmetic operator";
            break;
        case '(':
        case ')':
            std::cout << "Parenthesis";
            break;
        default:
            std::cout << "Other symbols";
            break;
    }
}