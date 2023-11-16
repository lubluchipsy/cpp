#include <iostream>
#include <string>


class Color 
{

public:
    
    Color(std::string & color): m_color(color){};
    Color(std::string && color): m_color(color){};

    void paint(std::string & new_color)
    {
        m_color = new_color;
    }

    std::string get_color() const
    {
        return m_color;
    }

private:

    std::string & m_color;

};


class Label 
{

public:

    Label(std::string & text): m_text(text){};
    Label(std::string && text): m_text(text){};

    void caps()
    {
        for(auto i = 0; i < m_text.size(); i += 1)
        {
            m_text[i] = char(toupper(m_text[i]));
        }
    }

    void set(std::string new_text)
    {
        m_text = new_text;
    }

    std::string get_text() const
    {
        return m_text;
    }

private:

    std::string & m_text;
};


template < typename ... Bases > 
class Point : public Bases...
{
public:

    explicit Point(Bases ... args, double x, double y) : Bases(args)..., m_x(x), m_y(y){};

    void set_x(double new_x)
    {
        m_x = new_x;
    }

    void set_y(double new_y)
    {
        m_y = new_y;
    }

    double get_x() const
    {
        return m_x;
    }

    double get_y() const
    {
        return m_y;
    }

private:

    double m_x;
    double m_y;

};



int main()
{
    std::string color = "yellow";
    std::string text = "point";

    Point < Color, Label > p1 ( Color("white"), Label(text), 2, 3 ); 

    p1.caps();
    p1.paint(color);

    std::cout << "Color is: " << p1.get_color() << "\n"
              << "Label is: " << p1.get_text() <<  "\n"
              << "(x, y) = " << "(" << p1.get_x() <<  ", " << p1.get_y() << ")"
              << std::endl;
    
    return 0;
}