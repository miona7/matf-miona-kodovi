#include "masterStudent.hpp"

MasterStudent::MasterStudent(const std::string& index, const std::string& name, StudyProgram program, 
    const std::vector<Grades>& grades, const std::string& mentor, const std::string& thesis) 
        : Student(index, name, program, grades), m_mentor(mentor), m_thesis(thesis) {}

std::string MasterStudent::info() const {
    return Student::info() + ", working on the thesis titled " + m_thesis + " under the mentorship of Prof. " + m_mentor;
}
