#pragma once

#include <vector>

class Point;
class Points;

std::vector<Points*> k_means(const std::vector<Point>& points, unsigned k);