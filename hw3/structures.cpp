#include <iostream>
#include<cstdlib>
#include<ctime>

const int max_lessons = 2;
const int max_students = 3;


struct Lesson;


struct Student
{
    std::string name;
    Lesson * lessons[max_lessons];
};


struct Lesson
{
    std::string name;
    Student * students[max_students];
};


int main()
{
    /*
    Here we create a random timetable for n_students students.
    Each student has max_lessons lessons which can repeat.
    There are n_lessons available lessons.
    */
   
    int n_students{};
    int n_lessons{};
    std::cout << "Input number of students: ";
    std::cin >> n_students;
    std::cout << "Input number of lessons: ";
    std::cin >> n_lessons;
    
    Student * students = new Student[n_students];
    Lesson * lessons = new Lesson[n_lessons];

    std::cout << "Input students' names: ";
    for(auto i = 0; i < n_students; i++)
    {
        std::cin >> students[i].name;
    }

    std::cout << "Input lessons' names: ";
    for(auto i = 0; i < n_lessons; i++)
    {
        std::cin >> lessons[i].name;
    }
    
    srand(time(NULL));

    for(auto i = 0; i < n_students; i++)
    {
        for(auto j = 0; j < max_lessons; j++)
        {
            int rand_lesson = rand() % n_lessons;
            students[i].lessons[j] = &lessons[rand_lesson];
        }
    }

    for(auto j = 0; j < n_students; j++)
    {
        std::cout << students[j].name << ": "; 
        for(auto i = 0; i < max_lessons; i++)
        {
            std::cout << students[j].lessons[i] -> name << ' ';
        }
        std::cout << '\n';
    }

    delete[] students;
    delete[] lessons;
}