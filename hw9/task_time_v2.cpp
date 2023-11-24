#include <iostream> 

// CRTP


template < typename T >
class CourseTime
{

public:

    double theory() 
    {
        return course()->theory_impl();
    }

    double homework() 
    {
        return course()->homework_impl();
    }

    double attendance() 
    {
        return course()->attendance_impl();
    }

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

private:

    T* course() 
        {
            return static_cast < T* >(this);
        }
    
};


class MathAnalysis: public CourseTime < MathAnalysis >
{

public:

    explicit MathAnalysis(double halyavnost, double lector_multiplicator): halyavnost_(halyavnost), lector_multiplicator_(lector_multiplicator){};

    double theory_impl() const
    {
        return 14 * 1.5 / lector_multiplicator_;  //watching lectures
    }

    double homework_impl() const 
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

    double attendance_impl() const 
    {
        return 14 * 1.5;  // attending seminars
    }
    
private:
    
    double halyavnost_;
    double lector_multiplicator_;  

};


class Cpp: public CourseTime < Cpp >
{

public:

    explicit Cpp(int topics_per_class): topics_per_class_(topics_per_class){};

    double theory_impl() const 
    {
        return 14 * 0.25 * topics_per_class_;  // spending 15 mins on 1 topic
    }

    double attendance_impl() const
    {
        return 14 * 3;
    }

    double homework_impl() const
    {
        return 14 * 3 * topics_per_class_; 
    }

private:

    int topics_per_class_;

};


int main()
{
    MathAnalysis maths(3, 1.25);

    Cpp cpp(3);

    std::cout << "Time needed to get 8 on cpp: " << cpp.calculate_time(8) << std::endl;
    std::cout << "Time needed to get 8 on math analysis: " << maths.calculate_time(8) << std::endl;

    return 0;
}


// Используя паттерн CRTP мы пользуемся одновременно преимуществами динамического и статического полиморфизма.
// Мы реализуем механизм виртуальных функций без использования виртуальных функций,
// тем самым избегая увеличения времени выполнения кода и дополнительных затрат памяти.
// Недостаток CRTP заключается в том, что базовые классы у производных получаются разные за счет использования шаблонов, 
// и объекты производных не получится поместить в один контейнер.
