#include <iostream>
#include <source_location>



class Logger
{
public:

    Logger(const std::source_location& source = std::source_location::current()): m_source(source)
    {
        std::cout << "Starting function " << m_source.function_name() << " at "
                  << m_source.file_name() << ":" << " line " << m_source.line() << std::endl;
    };

    ~Logger()
    {
        std::cout << "Ending function " << m_source.function_name() << " at "
                  << m_source.file_name() << ":" << " line " << m_source.line() << std::endl;
    };

private:

    std::source_location m_source;

};

void foo()
{
    Logger logger;
    std::cout << "Executing function" << std::endl;
}


int main()
{
    foo();
    return 0;
}