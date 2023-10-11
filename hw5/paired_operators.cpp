class A
{
public:

    int& method()
    {
        return const_cast<int&>(static_cast<const A&>(*this).method());
    }
    
    const int& method() const
    {
        return a;
    }

private:

    int a;
};