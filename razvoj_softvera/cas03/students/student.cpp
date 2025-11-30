#include "student.hpp"
#include <numeric>

Student::Student(const std::string& index, const std::string& name, StudyProgram program, const std::vector<Grades>& grades) 
    : m_index(index), m_name(name), m_program(program), m_grades(grades) {}

Student::~Student() = default;

double Student::gpa() const {
    unsigned sum = std::accumulate(m_grades.begin(), m_grades.end(), 0u, 
                        [&](unsigned acc, Grades g) { 
                            return acc + grade(g);
                        }); // grade je metod klase pa moramo to i naglasiti sa & ili sa this
    // unsigned sum = 0;
    // for(auto g : m_grades) {
    //     sum += grade(g);
    // }
    return sum / static_cast<double>(m_grades.size());
}

std::string Student::info() const {
    return "Student " + m_name + " " + m_index + " styding " + program_name() + " has a gpa of " + std::to_string(gpa());   
}

std::string Student::program_name() const {
    switch(m_program) {
        case StudyProgram::Informatics:
            return "informatics";

        case StudyProgram::Mathematics:
            return "mathematics";

        case StudyProgram::Astronomy:
            return "astronomy";
    }
}

unsigned Student::grade(Grades g) const {
    switch(g) {
        case Grades::Six:
            return 6;

        case Grades::Seven:
            return 7;

        case Grades::Eight:
            return 8;
        
        case Grades::Nine:
            return 9;

        case Grades::Ten:
            return 10;
    }
}