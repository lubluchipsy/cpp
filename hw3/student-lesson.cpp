#include <iostream>
#include <string>


class Student;


class Lesson
{
public:
    Lesson(const std::string & name) : m_name(name) {}

    const auto & name() const
	{
		return m_name;
	}

    void add_student(Student * student)
	{
		if (m_counter < max_students)
		{
			m_students[m_counter++] = student;
		}
		else
		{
			std::cout << "error: too many students" << std::endl;
		}
	}

    void show_students() const;

private:
    std::string m_name;

    static inline const int max_students = 100;

    Student * m_students[max_students]{};

    int m_counter = 0;
};





class Student
{
public:
	Student(const std::string & name) : m_name(name) {}

public:

	const auto & name() const
	{
		return m_name;
	}

	void add_lesson(Lesson * lesson)
	{
		if (m_counter < max_lessons)
		{
			m_lessons[m_counter++] = lesson;
		}
		else
		{
			std::cout << "error: too many lessons" << std::endl;
		}
	}

	void show_lessons() const;

private:

	static inline const int max_lessons = 100;

private:

	std::string m_name;

	Lesson * m_lessons[max_lessons]{};

	int m_counter = 0;
};

void Lesson::show_students() const
{
	std::cout << "Lesson " << m_name << " is visited by: " << std::endl;

	for (auto i = 0; i < m_counter; ++i)
	{
		std::cout << i + 1 << ": " << m_students[i]->name() << std::endl;
	}
}

void Student::show_lessons() const
{
	std::cout << "Student " << m_name << " visits: " << std::endl;

	for (auto i = 0; i < m_counter; ++i)
	{
		std::cout << i + 1 << ": " << m_lessons[i]->name() << std::endl;
	}
}

void connect(Student * s, Lesson * l)
{
	s->add_lesson(l); l->add_student(s);
}

int main()
{
	Student s1("Ivan");
	Student s2("Dmitriy");
	Student s3("Alexander");
	
	Lesson l1("Math");
	Lesson l2("Physics");
	Lesson l3("Literature");

	connect(&s1, &l1);
	connect(&s2, &l2);
	connect(&s3, &l3);
	connect(&s1, &l3);
	connect(&s2, &l1);
	connect(&s3, &l2);

	s1.show_lessons();

	l1.show_students();

	return 0;
}