#include <iostream> 

// Template method 


class CourseTime
{

public:

    virtual double theory() = 0;  // time spent on researching theory
    virtual double homework() = 0;  // time spent on doing homework
    virtual double attendance() = 0;  // time spent on attending classes

    double calculate_time(int rate)
    {
        if (rate < 3)
        {
            std::cout << "Relax!";
            return 0;
        }

        if (rate > 2 and rate < 5)
        {
            return homework();
        }

        if (rate > 4 and rate < 8)
        {
            return homework() + attendance();
        }

        if (rate > 7)
        {
            return homework() + attendance() + theory();
        }
    }

    virtual ~CourseTime(){};

};


class MathAnalysis: public CourseTime
{

public:

    MathAnalysis(double halyavnost, double lector_multiplicator): halyavnost_(halyavnost), lector_multiplicator_(lector_multiplicator){};

    double theory() override
    {
        return 14 * 1.5 / lector_multiplicator_;  //watching lectures
    }

    double homework() override
    {
        if (halyavnost_ > 4.5)
        {
            return 0.25;  // taking photos of a friend's notebook and sending them
        }

        if (halyavnost_ > 4 and halyavnost_ <= 4.5)
        {
            return 3;  // copying task
        }

        if (halyavnost_ <= 4)
        {
            return (14 * 5) / (halyavnost_ / 5);  // doing task yourself, the higher is halyavnost, the less effort you can put in it
        }
    }

    double attendance() override
    {
        return 14 * 1.5;  // attending seminars
    }
    

private:
    
    double halyavnost_;
    double lector_multiplicator_;  

};


class Cpp: public CourseTime
{

public:

    Cpp(int topics_per_class): topics_per_class_(topics_per_class){};

    double theory() override
    {
        return 14 * 0.25 * topics_per_class_;  // spending 15 mins on 1 topic
    }

    double attendance() override
    {
        return 14 * 3;
    }

    double homework() override
    {
        return 14 * 3 * topics_per_class_; 
    }

private:

    int topics_per_class_;

};


int main()
{
    MathAnalysis maths(4, 1.25);

    Cpp cpp(3);

    std::cout << "Time needed to get 8 on cpp: " << cpp.calculate_time(8) << std::endl;
    std::cout << "Time needed to get 8 on math analysis: " << maths.calculate_time(8) << std::endl;

    return 0;
}


// При шаблонном методе мы используем динамический полиморфизм. 
// Он дает нам преимущества в виде иерархии, полного интерфейса, но в runtime код будет выполняться долго,
// так как будет тратиться время на поиск нужной виртуальной функции в таблице.
// Также будет тратиться память на хранение виртуальных таблиц и указателей.