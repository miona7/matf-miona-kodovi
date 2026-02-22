#pragma once

#include <utility>
#include <string>
#include <vector>

using coordinates_t = std::pair<double, double>;

class Point {
    coordinates_t m_coords;
    const std::string m_name;

public:
    Point(const std::string& name, double x = 0.0, double y = 0.0);
    Point(const Point&);

    inline std::string getName() const {return m_name;}
    double getX() const;
    double getY() const;

    void setX(double);
    void setY(double);
    void setXY(double x, double y);

    static Point fromString(const std::string&);
    std::string toString() const;

    double distance(const Point& other) const;
    static std::vector<Point> readPoints(std::string fileName);
};