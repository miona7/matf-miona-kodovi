#pragma once

#include <random>

class RandomEngine{
    std::uniform_real_distribution<double> m_unif;
    std::default_random_engine m_re;

public:
    RandomEngine();

    double operator()();
    void setSeed(unsigned long seed);
};