#include "travelerworker.h"

TravelerWorker::TravelerWorker(QList<City*>* cities) : m_cities(cities) {}

void TravelerWorker::run() {
    unsigned steps = static_cast<unsigned>(QRandomGenerator::global()->bounded(3, 8));

    m_distance = 0;
    for(unsigned i = 0; i < steps; i++) {
        QThread::msleep(static_cast<unsigned long>(QRandomGenerator::global()->bounded(250, 501)));

        unsigned index = static_cast<unsigned>(QRandomGenerator::global()->bounded(m_cities->size()));
        const auto city = (*m_cities)[index];
        if(i == 0) {
            m_currCity = city;

            QMutexLocker lock(m_currCity->getMutex());
            const auto article = m_currCity->getRandomArticle();
            emit tookArticle(article);
        } else {
            if(m_currCity->getName() == city->getName()) {
                i--;
            } else {
                m_distance += m_currCity->distance(*city);
                m_currCity = city;

                QMutexLocker lock(m_currCity->getMutex());
                const auto article = m_currCity->getRandomArticle();
                emit tookArticle(article);
            }
        }
    }

    emit menhetnDistance(m_distance);
}
