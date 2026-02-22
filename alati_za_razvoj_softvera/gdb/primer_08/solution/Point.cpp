#include "Point.hpp"

#include <cmath>
#include <fstream>
#include <vector>

Point::Point(const std::string& name, double x, double y)
    : m_coords(std::make_pair(x, y)), m_name(name) {}

Point::Point(const Point& p)
    : m_coords(p.m_coords), m_name(p.m_name) {}


double Point::getX() const {
    return m_coords.first;
}

double Point::getY() const {
    return m_coords.second;
}

void Point::setX(double x){
    m_coords.first = x;
}

void Point::setY(double y){
    m_coords.second = y;
}

void Point::setXY(double x, double y){
    setX(x);
    setY(y);
}

Point Point::fromString(const std::string& str){
    std::string name;
    
    unsigned i = 0u;
    while (i < str.size() && str[i] != ':'){
        name.push_back(str[i]);
        ++i;
    }
    
    if (i == str.size()){
        return Point(name);
    }

    std::size_t read_character_n;

    ++i; // zbog :

    while (i < str.size() && str[i] == ' '){
        ++i;
    }

    const double x = std::stod(str.c_str() + i, &read_character_n);
    i += read_character_n;

    ++i; 

    while (i < str.size() && str[i] != ' '){
        ++i;
    }

    const double y = std::stod(str.c_str() + i);

    return Point(name, x, y);
}

std::string Point::toString() const{
    return m_name + ": " + std::to_string(getX()) + ", " + std::to_string(getY());
}

double Point::distance(const Point& other) const {
    const auto first = (getX() - other.getX())*(getX() - other.getX()); // getY -> getX
    const auto second = (getY() - other.getY())*(getY() - other.getY());
    return std::sqrt(first + second);
}

std::vector<Point> Point::readPoints(std::string fileName){
    std::vector<Point> points;
    // std::ifstream file(fileName + ".input");
    std::ifstream file(fileName);
    std::string line;

    while(std::getline(file, line)){
        points.push_back(Point::fromString(line));
    }
    file.close();

    return points;
}