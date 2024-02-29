#include <iostream>
#include <vector>
#include <cassert>


template <typename T>
class Stack
{
public:

    void push(T x)
    {
        if (s.empty())
        {
            s.push_back(x);
            min = x;
        }
        else
        {
            if (x >= min)
            {
                s.push_back(x);
            }
            if (x < min)
            {
                s.push_back(2*x - min);
                min = x;
            }
        }
    }

    void pop()
    {
        T y{s.back()};

        if (y >= min)
        {
            s.pop_back();
        }
        if (y < min)
        {
            min = 2*min - y;
            s.pop_back();  
        }
    }

    T top()
    {
        if (s.back() >= min)
        {
            return s.back();
        }
        if (s.back() < min)
        {
            return min;
        }

        return 0;
    }

    bool empty()
    {
        return s.empty();
    }

    std::size_t size()
    {
        return s.size();
    }

    T get_min()
    {
        return min;
    }

private:

    T min;
    std::vector <T> s;

};


int main()
{
    Stack <int> stack;

    stack.push(5);
    assert(stack.get_min() == 5);
    stack.push(3);
    assert(stack.get_min()   == 3);
    stack.push(4);
    assert(stack.get_min() == 3);
    stack.push(1);
    assert(stack.get_min() == 1);

    std::cout << "Stack: ";
    while (!stack.empty())
    {
        std::cout << stack.top() << " ";
        stack.pop();
    }
    std::cout << std::endl;

    return 0;
}