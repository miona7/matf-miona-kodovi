#include "vehiclePark.hpp"

// VehiclePark::VehiclePark() = default;

VehiclePark::VehiclePark(const VehiclePark& vp) {
    for(auto v : vp.m_vehicles) {
        m_vehicles.push_back(v->copy());
    }
}

// VehiclePark VehiclePark::operator=(const VehiclePark& vp) = delete;

VehiclePark::~VehiclePark() {
    for(auto v : m_vehicles) {
        delete v;
    }
}

void VehiclePark::add(Vehicle* v) {
    m_vehicles.push_back(v);
}

std::ostream& operator<<(std::ostream& s, const VehiclePark& vp) {
    for(auto v : vp.m_vehicles) {
        s << *v << std::endl;
    }
    return s;
}