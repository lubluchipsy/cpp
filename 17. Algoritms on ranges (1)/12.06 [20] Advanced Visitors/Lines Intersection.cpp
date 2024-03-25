#include <iostream>
#include <variant>

struct Point;

struct Line;

using CrossPoints = std::variant < Point, std::monostate, Line >;


struct Point
{
    Point(double x, double y): x_(x), y_(y){};

    double x_;
    double y_;

};


struct Line 
{
    Line(double a, double b, double c): a_(a), b_(b), c_(c){};

    double a_;
    double b_;
    double c_;

};


CrossPoints find_crossings(const Line & l1, const Line & l2)
{
    double det = (l1.a_ * l2.b_) - (l2.a_ * l1.b_);

    if (det == 0)
    {
        if ((l1.a_ * l2.c_) == (l2.a_ * l1.c_) & (l1.b_ * l2.c_) == (l2.b_ * l1.c_)) 
        {
            return l1;
        }

        else
        {
            return std::monostate();
        }
    }

    else
    {
        double x = (l2.c_ * l1.b_ - l1.c_ * l2.b_) / det;
        double y = (l2.a_ * l1.c_ - l1.a_ * l2.c_) / det;

        return Point(x, y);
    }
}


struct Printer
{
    void operator()(const Line & line) const
    {
        std::cout << line.a_ << "x + " << line.b_ << "y + " << line.c_ << " = 0" << std::endl;
    }
    void operator()(const Point & point) const
    {
        std::cout << "Crossing point: " << "(" << point.x_ << ", " << point.y_ << ")" << std::endl;
    }
    void operator()(const std::monostate & monostate) const
    {
        std::cout << "Lines do not cross." << std::endl;
    }
};


int main()
{
    std::visit(Printer{}, find_crossings(Line(2, 1, 3), Line(6, 3, 2)));
    
    std::visit(Printer{}, find_crossings(Line(2, 1, 3), Line(6, 3, 9)));

    std::visit(Printer{}, find_crossings(Line(2, 1, 3), Line(2, 2, 2)));

    return 0;
}