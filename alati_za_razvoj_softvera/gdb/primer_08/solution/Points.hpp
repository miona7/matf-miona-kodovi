#pragma once

#include <vector>

class Point;
class RandomEngine;
using points_t = std::vector<Point>;
using names_t = std::vector<std::string>;

class Points{
    points_t m_points;
    Point m_centroid;

public:
    Points();
    Points(const Points&);

    Point getCentroid() const;
    double getDistancesFromCentroid() const;
    names_t getNames() const;

    void calculateCentroid();

    void clear();
    size_t size() const;
    void add_point(const Point);

    static RandomEngine s_re;
};