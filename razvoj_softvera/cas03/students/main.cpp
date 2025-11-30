#include <iostream>
#include "student.hpp"
#include "masterStudent.hpp"

int main() {
    Student s1("133/2022", "Miona Sretenovic", StudyProgram::Informatics, {Grades::Seven, Grades::Eight, Grades::Ten, Grades::Ten, Grades::Ten});
    std::cout << s1.info() << std::endl;

    MasterStudent s2("100/2025", "Pera Peric", StudyProgram::Mathematics, {Grades::Ten, Grades::Ten}, "Zlatko Lazovic", "Analisys");
    std::cout << s2.info() << std::endl;

    // odsecanje
    Student s3 = MasterStudent("101/2025", "Laza Lazarevic", StudyProgram::Astronomy, {Grades::Six}, "Devito i Bajaga", "Astronaut");
    std::cout << s3.info() << std::endl;

    // pokazivaci omogucavaju polimorfizam
    Student* s4 = new MasterStudent("133/2025", "Miona Sretenovic", StudyProgram::Informatics, {Grades::Ten, Grades::Ten, Grades::Ten}, "Predrag Janicic", "CNN");
    std::cout << s4->info() << std::endl;
    delete s4;
}