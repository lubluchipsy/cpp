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


// Passkey pattern

class Key
{
friend class B;
};

class A 
{
public:
    void get_secret(Key & key)
    {
        std::cout << "secret data: " << secret_data;
    }

private:
    const int secret_data{777};
    int other_secret{};
friend class Key;
};

class B 
{
public:
    void get_A_secret(Key & key) 
    {
        A a;
        a.get_secret(key);
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
    B b;
    Key key;
    b.get_A_secret(key);
}


