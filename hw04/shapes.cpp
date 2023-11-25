#include <iostream>
#include <math.h>


class Shape
{
public:
    virtual double perimeter() const = 0;
    virtual double area() const = 0;
    virtual ~Shape() {};
};


class Polygon : public Shape
{
};


class Rectangle : public Polygon
{
public:
    Rectangle(double a = 0.0, double b = 0.0) : m_a(a), m_b(b)
    {
    }

    double perimeter() const override
    {
        return 2 * (m_a + m_b);
    }

    double area() const override
    {
        return m_a * m_b;
    }

private:
    double m_a;
    double m_b;
};


class Square: public Rectangle
{
public:
    Square(double a = 0.0)
        : Rectangle(a, a)
    {
    }
};


class Triangle : public Polygon
{
public:
    Triangle(double a = 0.0, double b = 0.0, double c = 0.0) : m_a(a), m_b(b), m_c(c)
    {
        if(m_a > (m_b + m_c) || m_b > (m_a + m_c) || m_c > (m_b + m_a))  //doesn't exist
        {
            m_a = 0;
            m_b = 0;
            m_c = 0;

            std::cout << "Triangle doesn't exist." << std::endl;
        }
    }

    double perimeter() const override
    {
        return (m_a + m_b + m_c);
    }

    double area() const override
    {   
        auto p = 0.5 * perimeter();

        return (sqrt(p*(p - m_a)*(p - m_b)*(p - m_c)));
    }

private:
    double m_a;
    double m_b;
    double m_c;
};


class Ellipse : public Shape
{
static inline const auto pi = 3.14;

public:
    Ellipse(double a = 0.0, double b = 0.0) : m_a(a), m_b(b)
    {
    }

    double perimeter() const override
    {
        return (4*(pi*m_a*m_b - std::pow(m_a - m_b, 2))/(m_a + m_b));
    }

    double area() const override
    {
        return (pi * m_a * m_b);
    }

private:
    double m_a;
    double m_b;
};


class Circle : public Ellipse
{
public:
    Circle(double r = 0.0)
        : Ellipse(r, r)
    {
    }
};


int main()
{
    auto size = 5;

    Shape * shapes[5];

    shapes[0] = new Rectangle(5,3);
    shapes[1] = new Square(4);
    shapes[2] = new Triangle(3, 4, 5);
    shapes[3] = new Ellipse(5, 3);
    shapes[4] = new Circle(4);


    std::cout << "Areas: ";

    for(auto i = 0; i < size; i++)
    {
        std::cout << shapes[i]->area() << "  ";
    }

    std::cout << "\n" << "Perimeters: ";

    for(auto i = 0; i < size; i++)
    {
        std::cout << shapes[i]->perimeter() << "  ";
    }

    for (auto i = 0; i < 5; i++)
    {
        delete shapes[i];
    }

    return 0;
}
