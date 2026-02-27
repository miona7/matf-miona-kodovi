#include "hunterworker.h"

HunterWorker::HunterWorker(QList<TreasureHunter*>* hunters, unsigned index, QMutex* mutex, TreasureMap* map, double gameSpeed)
    : m_hunters(hunters), m_index(index), m_mutex(mutex), m_map(map), m_gameSpeed(gameSpeed) {
}

void HunterWorker::run() {
    TreasureHunter* hunter = (*m_hunters)[m_index];

    while(m_map->hasDucats()) {
        QThread::msleep(100 / (hunter->getSpeed() * m_gameSpeed) * 1000);

        QMutexLocker lock(m_mutex);

        auto positions = m_map->getMovableFrom(hunter->getPosition());
        for(const auto& h : *m_hunters) {
            positions.removeIf([&h](const auto& pos) {
                return h->getPosition() == pos;
            });
        }

        if(!positions.empty()) {
            const auto move = positions[QRandomGenerator::global()->bounded(positions.size())];
            emit hunterMoved(hunter->getPosition(), move);
            hunter->setPosition(move);

            if(m_map->grabTreasure(move)) {
                hunter->addDucats(QRandomGenerator::global()->bounded(1, 6));
                emit hunterFoundTreasure(m_index);
            }
        }
    }
}
