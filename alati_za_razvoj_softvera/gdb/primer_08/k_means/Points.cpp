#include "Point.hpp"
#include "Points.hpp"
#include "RandomEngine.hpp"

RandomEngine Points::s_re = RandomEngine(); 

Points::Points()
    : m_centroid("centroid") {
    double x = Points::s_re();
    double y = Points::s_re();

    m_centroid.setXY(x, y);
}

Points::Points(const Points& other)
    : m_points(other.m_points), m_centroid(other.m_centroid) {}

Point Points::getCentroid() const{
    return m_centroid;
}

double Points::getDistancesFromCentroid() const{
    double distance = 0.0;
    for(const auto& p : m_points){
        distance += m_centroid.distance(p);
    }

    return distance;
}

names_t Points::getNames() const{
    names_t names;
    for (auto& p : m_points){
        names.push_back(p.getName());
    }

    return names;
}

void Points::calculateCentroid(){
    double x = 0.0, y = 0.0;

    for(const auto& p : m_points){
        x += p.getX();
        y += p.getY();
    }

    x /= size();
    y /= size();

    m_centroid.setXY(x, y);
}

void Points::clear(){
    m_points.clear();
}

size_t Points::size() const {
    return m_points.size();
}

void Points::add_point(const Point p){
    m_points.push_back(p);
}
