#include "car.hpp"

Car::Car(unsigned wheels, unsigned seats, unsigned windows) : VehicleWithWindows(wheels, seats, windows) {}

std::string Car::type() const {
    return "car";
}

Vehicle* Car::copy() const {
    // poziva se podrazumevani konstruktor kopije, nismo pisali nas jer radimo sa primitivnim tipovima, ovo ne bi bilo validno da imamo dinamicke resurse 
    return new Car(*this);
}