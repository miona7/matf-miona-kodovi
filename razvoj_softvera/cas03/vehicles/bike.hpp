#ifndef BIKE_HPP
#define BIKE_HPP

#include "vehicles.hpp"

class Bike : public Vehicle {
    public:
        Bike(unsigned, unsigned);

        std::string type() const override;
        Vehicle* copy() const override;
};

#endif // BIKE_HPP