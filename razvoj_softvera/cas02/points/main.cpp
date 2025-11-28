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

    Point* p2 = new Point{1.2, 2.3};
    p2->print(); 
    delete p2;

    Point* points = new Point[] { {1.2, 3.7}, {8.9, 9.5} };
    for(int i = 0; i < 2; i++) {
        points[i].print();
    }
    delete[] points; 
}