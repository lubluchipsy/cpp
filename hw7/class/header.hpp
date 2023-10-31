#include <iostream>

struct PrintString {
    PrintString() {
        std::cout << "Hello, World!" << std::endl;
    }
};

PrintString printString;

int main() {}