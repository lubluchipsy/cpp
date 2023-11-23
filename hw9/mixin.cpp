#include <iostream>
#include <string>


class Color 
{

public:
    
    Color(const std::string & color): m_color(color){};

    void paint(const std::string & new_color)
    {
        m_color = new_color;
    }

    const auto & show() const
    {
        return m_color;
    }

private:

    std::string m_color;

};


class Label 
{

public:

    Label(const std::string & text): m_text(text){};

    void caps()
    {
        for(auto i = 0; i < m_text.size(); i += 1)
        {
            m_text[i] = char(toupper(m_text[i]));
        }
    }

    void clear()
    {
        m_text.erase();
    }

    void add(const std::string & text)
    {
        m_text += text;
    }

    auto & print() const
    {
        return m_text;
    }

private:

    std::string m_text;
};


template < class ... Bases > 
class Point : public Bases...
{
public:

    template < typename ... Types >  explicit Point(double x, double y, const Types& ... args) : m_x(x), m_y(y), Bases(args)...{};

    void show_position()
    {
        std::cout << "(" << m_x << ", " << m_y << ")";
    }

    double m_x;
    double m_y;

};



int main()
{
    std::string color = "yellow";
    std::string text = "point";

    Point < Color, Label > p1 (2, 3, "white", "point"); 

    p1.caps();
    p1.paint(color);

    std::cout << p1.show() << std::endl;
    std::cout << p1.print() << std::endl;
    p1.show_position();

    return 0;
}