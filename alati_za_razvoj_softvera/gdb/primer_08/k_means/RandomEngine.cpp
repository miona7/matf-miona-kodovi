#include "RandomEngine.hpp"

RandomEngine::RandomEngine()
    : m_unif(-100.0, 100.0){}

void RandomEngine::setSeed(unsigned long seed) {
    m_re.seed(seed);
}

double RandomEngine::operator()(){
    return m_unif(m_re);
}