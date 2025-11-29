#ifndef STUDENT_HPP
#define STUDENT_HPP

// umesto guard makroa mozemo koristiti #pragma once direktivu ali ona nije podrzana standardom

#include <string>
#include <vector>

enum class StudyProgram {
    Informatics,
    Mathematics,
    Astronomy
};

enum class Grades {
    Six,
    Seven, 
    Eight,
    Nine,
    Ten
};

class Student {
    public:
        Student(const std::string&, const std::string&, StudyProgram, const std::vector<Grades>&);
        virtual ~Student();

        double gpa() const;
        virtual std::string info() const;

    private:
        std::string m_index;
        std::string m_name;
        StudyProgram m_program;
        std::vector<Grades> m_grades;

        std::string program_name() const;
        unsigned grade(Grades) const;
};

#endif // STUDENT_HPP