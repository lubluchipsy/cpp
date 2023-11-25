#include <iostream>
#include <math.h>

class Triangle
{
public:
    Triangle() : m_a(0), m_b(0), m_c(0)
    {
    }

    Triangle(double a, double b, double c) : m_a(a), m_b(b), m_c(c)
    {
        if(m_a > (m_b + m_c) || m_b > (m_a + m_c) || m_c > (m_b + m_a))  //doesn't exist
        {
            m_a = 0;
            m_b = 0;
            m_c = 0;
        }
    }

    double perimeter() const
    {
        return (m_a + m_b + m_c);
    }

    double area() const
    {   
        auto p = 0.5 * perimeter();

        return (sqrt(p*(p - m_a)*(p - m_b)*(p - m_c)));
    }

    double get_a() const
    {
        return m_a;
    }

    double get_b() const
    {
        return m_b;
    }

    double get_c() const
    {
        return m_c;
    }

private:
    double m_a;
    double m_b;
    double m_c;
};


class Square
{
public:
    Square() : m_a(0)
    {
    }

    Square(double a) : m_a(a)
    {
    }

    double perimeter() const
    {
        return (m_a * 4);
    }

    double area() const
    {   
        return (m_a * m_a);
    }

    double get_a() const
    {
        return m_a;
    }
    
private:
    double m_a;
};


class Circle
{
public:
    Circle() : m_r(0)
    {
    }

    Circle(double r) : m_r(r)
    {
    }

    double perimeter() const
    {
        return 2 * 3.14 * m_r;
    }

    double area() const
    {
        return 3.14 * m_r * m_r;
    }
    
private:
    double m_r;
};


int main()
{
    double a{};
    double b{};
    double c{};
    std::cout << "Input sizes of triangle's sides: ";
    std::cin >> a >> b >> c;
    Triangle t(a, b, c);
    std::cout << "The area of the triangle is: " << t.area() << '\n';
    std::cout << "The perimeter of the triangle is: " << t.perimeter() << '\n' << '\n';

    std::cout << "Input size of square's side: ";
    std::cin >> a;
    Square s(a);
    std::cout << "The area of the square is: " << s.area() << '\n';
    std::cout << "The perimeter of the square is: " << s.perimeter() << '\n' << '\n';

    double r{};
    std::cout << "Input size of circle's radius: ";
    std::cin >> r;
    std::cout << r;
    Circle o(r);
    std::cout << "The area of the circle is: " << o.area() << '\n';
    std::cout << "The perimeter of the circle is: " << o.perimeter() << '\n';

    return 0;
}
