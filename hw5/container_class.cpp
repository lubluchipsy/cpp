/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>


class Container
{
public:

    using data_t = int;
    using size_t = int;
    using capacity_t = int;

    Container() : m_data(nullptr), m_size(0), m_capacity(0)  //default constructor
	{
	}

    Container(capacity_t capacity) : m_capacity(capacity), m_size(0)  //constructor
	{
		m_data = new data_t[m_capacity]{};
	}

    Container(const Container & other) : m_size(other.m_size), m_capacity(other.m_capacity)  //copy constructor
	{
		m_data = new data_t[m_capacity];

		for (size_t i = 0; i < m_size; ++i) 
		{
			m_data[i] = other.m_data[i];
		}
	}

    Container(Container && other) : Container()  //move constructor
	{
		swap(other);
	}

    Container & operator=(Container other)  //copy assignment
	{
		swap(other);

		return *this;
	}

	void swap(Container & other)
	{
		using std::swap;

		swap(m_data, other.m_data);
        swap(m_capacity, other.m_capacity);
		swap(m_size, other.m_size);
	}

	~Container()  //destructor
	{
    if (m_data)
		{
			delete[] m_data;
		}
	}

    size_t get_size() const //size getter
    {
        return m_size;
    }

    capacity_t get_capacity() const //capacity getter
    {
        return m_capacity;
    }

    data_t front()
    {
        return m_data[0];
    }
    
    const data_t front() const
    {
        return m_data[0];
    }

    data_t back()
    {
        return m_data[m_size - 1];
    }
    
    const data_t back() const
    {
        return m_data[m_size - 1];
    }

    data_t& operator[](int i)  //we are returning lvalue reference to be able to assign elements with this operator
    {
        return m_data[i];
    }

    const data_t& operator[](int i) const  //operator for const arrays, we can use it only for getting elements
    {
        return m_data[i];
    }

    void push_back(const data_t value)
    {
        if(m_size >= m_capacity)  //if we don't have enough memory
        {
            auto new_capacity = m_capacity == 0 ? 1 : 2*m_capacity;  //double capacity 
            auto new_data = new data_t[new_capacity];  //making new array with double capacity

            for(auto i = 0; i < m_size; i++)  //copying values into the new array
            {
                new_data[i] = m_data[i];
            }
            delete[] m_data;  //deleting old array
            m_data = new_data;          //assigning data and capacity with new values
            m_capacity = new_capacity;
        }

        m_data[m_size++] = value;  //adding element to the array
    }

    bool empty()
    {
        return (m_size ? true : false);
    }

    void clear()
    {
        m_size = 0;
    }

private:

    data_t * m_data;
    size_t m_size;
    capacity_t m_capacity;

};


int main()
{
    Container c;
    c.push_back(42);
    c.push_back(2);
    std::cout << c.get_capacity()<< std::endl;
    std::cout << c.get_size() << std::endl;
    std::cout << c[0] << " ";
    std::cout << c[1];
    return 0;
}