#ifndef MASTER_STUDENT_HPP
#define MASTER_STUDENT_HPP

#include "student.hpp"

class MasterStudent : public Student {
    public:
        MasterStudent(const std::string&, const std::string&, StudyProgram, const std::vector<Grades>&, const std::string&, const std::string&);

        std::string info() const override;

    private:
        std::string m_mentor;
        std::string m_thesis;
};

#endif // MASTER_STUDENT_HPP