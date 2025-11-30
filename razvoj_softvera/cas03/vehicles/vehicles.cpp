#include "vehicles.hpp"

Vehicle::Vehicle(unsigned wheels, unsigned seats) : m_wheels(wheels), m_seats(seats) {}

Vehicle::~Vehicle() = default;

void Vehicle::print(std::ostream& s) const {
    s << "type: " << type() << ", wheels: " << m_wheels << ", seats: " << m_seats;
}

std::ostream& operator<<(std::ostream& s, const Vehicle& v) {
    v.print(s);
    return s;
}
