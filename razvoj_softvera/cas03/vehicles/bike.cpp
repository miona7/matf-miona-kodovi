#include "bike.hpp"

Bike::Bike(unsigned wheels, unsigned seats) : Vehicle(wheels, seats) {}

std::string Bike::type() const {
    return "bike";
}

Vehicle* Bike::copy() const {
    return new Bike(*this);
}