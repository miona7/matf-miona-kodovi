#include "vehiclesWithWindows.hpp"

VehicleWithWindows::VehicleWithWindows(unsigned wheels, unsigned seats, unsigned windows) : Vehicle(wheels, seats), m_windows(windows) {}

void VehicleWithWindows::print(std::ostream& s) const {
    Vehicle::print(s);
    s << ", windows: " << m_windows;
}