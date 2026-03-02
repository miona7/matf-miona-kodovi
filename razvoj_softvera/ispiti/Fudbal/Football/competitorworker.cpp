#include "competitorworker.h"

CompetitorWorker::CompetitorWorker(QList<Competitor*>* competitors, unsigned index, unsigned numOfTries)
    : m_competitors(competitors), m_index(index), m_numOfTries(numOfTries) {}

void CompetitorWorker::run() {
    auto competitor = (*m_competitors)[m_index];

    for(unsigned i = 0; i < m_numOfTries; i++) {
        const auto hit = QRandomGenerator::global()->generateDouble();
        if(hit <= competitor->getPrecision()) {
            competitor->addPoints(1);
            emit goal(true, m_index);
        } else {
            emit goal(false, m_index);
        }
    }
}
