#include <thread>
#include <iostream>
#include <vector>

int main()
{
    auto i = 0;
    std::vector <std::thread> threads{};
    while (true)
    {
        threads.push_back(std::thread([](){auto c=0; while(true){c++;};}));
        std::cout << threads.size() << "\n";
    }
}

/*
Этот код завершился после создания 8869 потоков на 64-битной системе и после создания 508 потоков на 32-битной системе. 
Теоритически для 32-разрядной системы есть 3 свободных ГБ адресного пространства. Для каждого потока нужно около 1 МБ для стека.
Тогда на 32-разрядной системе можно создать 3 ГБ / 1 МБ потоков, что равно 3072. В реальности число потоков в 6 раз меньше.
*/