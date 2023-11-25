#include <iostream>
#include <variant>

struct Point;

using CrossPoints = std::variant < Point, const char * >;


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
            return "Lines coincide.";
        }

        else
        {
            return "Lines are parallel.";
        }
    }

    else
    {
        double x = (l2.c_ * l1.b_ - l1.c_ * l2.b_) / det;
        double y = (l2.a_ * l1.c_ - l1.a_ * l2.c_) / det;

        return Point(x, y);
    }
}


void get_crossings(const CrossPoints & crossings)
{
    if (std::holds_alternative < const char *  > (crossings))
    {
        std::cout << std::get < const char * > (crossings) << std::endl;
    } 

    if (std::holds_alternative < Point > (crossings))
    {
        Point point = std::get < Point > (crossings);
        std::cout << "Crossing point: " << "(" << point.x_ << ", " << point.y_ << ")" << std::endl;
    } 
}



int main()
{
    get_crossings(find_crossings(Line(2, 1, 3), Line(6, 3, 2)));

    get_crossings(find_crossings(Line(2, 1, 3), Line(6, 3, 9)));

    get_crossings(find_crossings(Line(2, 1, 3), Line(2, 2, 2)));
}