#include <iostream>
#pragma once

class Container
{
public:

    Container() : m_data(nullptr), m_size(0), m_capacity(0)  //default constructor
	{
	}

    Container(int capacity);

    Container(const Container & other);

    Container(Container && other);

    Container & operator=(Container other);

	void swap(Container & other);

	~Container();
    

    int get_size() const //size getter
    {
        return m_size;
    }

    int get_capacity() const //capacity getter
    {
        return m_capacity;
    }

    int& front()
    {
        return m_data[0];
    }
    
    const int& front() const
    {
        return m_data[0];
    }

    int& back()
    {
        return m_data[m_size - 1];
    }
    
    const int& back() const
    {
        return m_data[m_size - 1];
    }

    int& operator[](int i)  //we are returning lvalue reference to be able to assign elements with this operator
    {
        return m_data[i];
    }

    const int& operator[](int i) const  //operator for const arrays, we can use it only for getting elements
    {
        return m_data[i];
    }

    void push_back(const int value);

    bool empty() const
    {
        return m_size == 0;
    }

    void clear()
    {
        m_size = 0;
    }

private:

    int * m_data;
    int m_size;
    int m_capacity;

};
