#include "container.hpp"
#include <iostream>


Container::Container(int capacity) : m_capacity(capacity), m_size(0)  //constructor
{
    m_data = new int[m_capacity]{};
}

Container::Container(const Container & other) : m_size(other.m_size), m_capacity(other.m_capacity)  //copy constructor
{
    m_data = new int[m_capacity];

    for (int i = 0; i < m_size; ++i) 
    {
        m_data[i] = other.m_data[i];
    }
}

Container::Container(Container && other) : Container()  //move constructor
{
    swap(other);
}

Container & Container::operator=(Container other)  //copy assignment
{
    swap(other);

    return *this;
}

Container::~Container()
    {
    if (m_data)
        {
            delete[] m_data;
        }
    }

void Container::swap(Container & other)
{
    using std::swap;

    swap(m_data, other.m_data);
    swap(m_capacity, other.m_capacity);
    swap(m_size, other.m_size);
}

void Container::push_back(const int value)
{
    if(m_size >= m_capacity)  //if we don't have enough memory
    {
        auto new_capacity = m_capacity == 0 ? 1 : 2*m_capacity;  //double capacity 
        auto new_data = new int[new_capacity];  //making new array with double capacity

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

