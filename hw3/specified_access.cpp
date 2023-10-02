#include <iostream>

//Attorney-client idiom

class Printer
{
private:
    void print_int(int a)
    {
        std::cout << a;
    }

    void print_double(double a)
    {
        std::cout << a;
    }

    void print_char(char a)
    {
        std::cout << a;
    }

    friend class Attorney;
};

class Attorney  // we are creating this class to get needed function from Printer
{
private:
    static void call_print_int(Printer & p, int a) 
    {
        p.print_int(a);
    }

    friend class Int_values; 
};

class Int_values // this class needs access to Printer's method print_int
{
public:
    Int_values(int value) : m_value(value)
    {
    }

    void print(Printer p)
    {
        Attorney att;
        att.call_print_int(p, m_value);
    }
private:
    int m_value{};
};


class Secret 
{   
    class ConstructorKey 
        {
        friend class SecretFactory;
        private:
            ConstructorKey() {};
            ConstructorKey(ConstructorKey const&) = default;
        };
public:
    Secret(std::string str, ConstructorKey) : data(std::move(str)) {}

private:
    void addData(std::string const& moreData);

    std::string data;
};


class SecretFactory 
{
public:
    Secret getSecret(std::string str) 
    {
    return Secret{std::move(str), {}};
    }
};


int main()
{
// Attorney-client demonstration
    Printer p{};
    Int_values i(5);
    i.print(p);
    std::cout << "\n";

// Passkey pattern demonstration
    SecretFactory sf;
    Secret s = sf.getSecret("moo!");

    return 0;
}

/*
Attorney-client idiom and Passkey pattern have same functions: they both give access to a specified set of class private data to another class.
In my opinion the Passkey pattern is easiar to read and understand.
*/
