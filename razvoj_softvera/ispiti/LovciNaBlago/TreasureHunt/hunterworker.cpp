#include "hunterworker.h"

HunterWorker::HunterWorker(TreasureHunter* hunter, TreasureMap* map, double gameSpeed)
    : m_hunter(hunter), m_map(map), m_gameSpeed(gameSpeed) {
}

void HunterWorker::run() {
    while(m_map->hasDucats()) {
        QThread::msleep(100 / (m_hunter->getSpeed() * m_gameSpeed) * 1000);

        auto positions = m_map->getMovableFrom(m_hunter->getPosition());

        if(!positions.empty()) {
            const auto move = positions[QRandomGenerator::global()->bounded(positions.size())];
            // emit hunterMoved();
            m_hunter->setPosition(move);

            if(m_map->grabTreasure(move)) {
                m_hunter->addDucats(QRandomGenerator::global()->bounded(1, 6));
            }
        }
    }
}
