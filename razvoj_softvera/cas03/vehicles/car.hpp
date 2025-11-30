#ifndef CAR_HPP
#define CAR_HPP

#include "vehiclesWithWindows.hpp"

class Car : public VehicleWithWindows {
    public:
        Car(unsigned, unsigned, unsigned);

        std::string type() const override;
        Vehicle* copy() const override;
};

#endif // CAR_HPP