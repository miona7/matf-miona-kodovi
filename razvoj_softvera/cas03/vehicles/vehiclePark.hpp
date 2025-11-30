#ifndef VEHICLEPARK_HPP
#define VEHICLEPARK_HPP

#include <iostream>
#include <vector>
#include "vehicles.hpp"

class VehiclePark {
    public:
        VehiclePark() = default;
        VehiclePark(const VehiclePark&);
        VehiclePark operator=(const VehiclePark&) = delete;
        ~VehiclePark();

        void add(Vehicle* v);

        friend std::ostream& operator<<(std::ostream&, const VehiclePark&);

    private:
        std::vector<Vehicle*> m_vehicles;
};

#endif // VEHICLEPARK_HPP