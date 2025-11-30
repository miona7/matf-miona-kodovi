#ifndef TRUCK_HPP
#define TRUCK_HPP

#include "vehiclesWithWindows.hpp"

class Truck : public VehicleWithWindows {
    public:
        Truck(unsigned, unsigned, unsigned);

        std::string type() const override;
        Vehicle* copy() const override;
};

#endif // TRUCK_HPP