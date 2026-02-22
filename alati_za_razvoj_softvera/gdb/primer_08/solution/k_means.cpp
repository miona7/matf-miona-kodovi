#include "Point.hpp"
#include "Points.hpp"

namespace {
    double distanceSum(const std::vector<Points*>& points){
        double distance = 0.0;
        for (auto p : points){
            distance += p->getDistancesFromCentroid();
        }
        return distance;
    }

    void step(const std::vector<Point>& point_list, std::vector<Points*>& points){
        for(auto p : points){
            p->clear();
        }

        for(auto p : point_list){
            Points* closest = nullptr;
            double closest_distance = 0.0;
            for(auto current : points){
                auto current_distance = p.distance(current->getCentroid());
                if (!closest || current_distance < closest_distance){
                    closest = current;
                    closest_distance = p.distance(current->getCentroid());
                }
            }
            closest->add_point(p);
        }

        for(auto p : points){
            p->calculateCentroid();
        }
    }

    const double EPSILON = 0.001;
}

std::vector<Points*> k_means(const std::vector<Point>& point_list, unsigned k){
    if(k == 0){
        return {};
    }

    if(k == 1){
        // Points points;
        Points* points = new Points();
        for(auto& p : point_list){
            // points.add_point(p);
            points->add_point(p);
        }
        // points.calculateCentroid();
        // return {&points};
        points->calculateCentroid();
        return {points};
    }

    std::vector<Points*> points;
    points.reserve(k);
    for(auto i = 0u; i < k; ++i){
        points.push_back(new Points());
    }

    auto distance_prev = distanceSum(points);
    step(point_list, points);
    auto distance = distanceSum(points);

    while(std::abs(distance - distance_prev) > EPSILON){
        distance_prev = distance;
        step(point_list, points);
        distance = distanceSum(points);
    }

    return points;
}