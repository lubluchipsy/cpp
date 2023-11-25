#include <iostream>

template <typename DrawingAPI> 
class Shape
{

public:

    Shape()
    {
        m_drawing_api = new DrawingAPI;
    };

    void draw()
    {
        m_drawing_api->draw();
    }

    ~Shape()
    {
        delete m_drawing_api;
    }

private:

    DrawingAPI * m_drawing_api;

};   


class DrawingTriangle
{
public:

    void draw()
    {
        std::cout << "Triangle" << std::endl;
    }

};


class DrawingCircle
{
public:

    void draw()
    {
        std::cout << "Circle" << std::endl;
    }
    
};


class Triangle: public Shape<DrawingTriangle>{};


class Circle: public Shape<DrawingCircle>{};


int main()
{
    
    Circle circle;

    Triangle triangle;

    circle.draw();

    triangle.draw();

}
