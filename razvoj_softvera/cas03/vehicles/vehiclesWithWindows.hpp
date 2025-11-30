#ifndef VEHICLESWITHWINDOWS_HPP
#define VEHICLESWITHWINDOWS_HPP

#include "vehicles.hpp"

class VehicleWithWindows : public Vehicle {
    protected:
        VehicleWithWindows(unsigned, unsigned, unsigned);
        void print(std::ostream&) const override;
    
    private:
        unsigned m_windows;
};

#endif // VEHICLESWITHWINDOWS_HPP
