#include <iostream>
#include "vehiclePark.hpp"
#include "car.hpp"
#include "truck.hpp"
#include "bike.hpp"

int main() {
    // Car c1(4, 4, 4);
    // std::cout << c1 << std::endl;

    // Car* c2 = new Car(4, 2, 2);
    // std::cout << *c2 << std::endl;
    // delete c2;

    // Truck t1(6, 3, 2);
    // std::cout << t1 << std::endl;

    // Truck* t2 = new Truck(8, 4, 6);
    // std::cout << *t2 << std::endl;
    // delete t2;

    // Bike b1(2, 1);
    // std::cout << b1 << std::endl;

    // Bike* b2 = new Bike(4, 2);
    // std::cout << *b2 << std::endl;
    // delete b2;

    VehiclePark park1;

    park1.add(new Car(4, 4, 4));
    park1.add(new Truck(6, 3, 2));
    park1.add(new Bike(2, 1));

    std::cout << park1 << std::endl;

    VehiclePark park2;

    park2.add(new Car(4, 2, 2));
    park2.add(new Truck(8, 4, 6));
    park2.add(new Bike(4, 2));

    std::cout << park2 << std::endl;


    VehiclePark park3 = park2;
    
    park3.add(new Car(10, 10, 10));

    std::cout << park3 << std::endl;
}