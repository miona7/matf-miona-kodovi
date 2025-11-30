#include "truck.hpp"

Truck::Truck(unsigned wheels, unsigned seats, unsigned windows) : VehicleWithWindows(wheels, seats, windows) {}

std::string Truck::type() const {
    return "truck";
}

Vehicle* Truck::copy() const {
    return new Truck(*this);
}