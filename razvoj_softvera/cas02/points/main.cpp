#include <iostream>

struct Point {
    void print() {
        std::cout << "(" << x << ", " << y << ")" << std::endl;
    } 

    double x;
    double y;
};

// u C++ klasa i struktura u sustini predstavljaju istu stvar, jedina razlika je u tome sto su kod klase sve promenljive podrazumevano privatne, a kod strukture javne 

int main() {
    Point p1 {3.5, 4.3};  // lista inicijalizacije, clanovi strukture se direktno inicijalizuju vrednostima
    p1.print();
}