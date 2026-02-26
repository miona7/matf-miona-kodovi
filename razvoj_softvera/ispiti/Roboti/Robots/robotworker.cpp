#include "robotworker.h"

RobotWorker::RobotWorker(Robot* r1, Robot* r2, int i, int j) : m_r1(r1), m_r2(r2), m_i(i), m_j(j) {
}

void RobotWorker::run() {
    QMutexLocker lockOne(m_r1->getBattleMutex());
    QMutexLocker lockTwo(m_r2->getBattleMutex());

    m_r1->setCurrLifePoints(m_r1->getMaxLifePoints());
    m_r2->setCurrLifePoints(m_r2->getMaxLifePoints());

    while(!m_r1->isDead() && !m_r2->isDead()) {
        QThread::msleep(250);
        int att = static_cast<int>(QRandomGenerator::global()->bounded(1, 3));

        if(att == 1 && m_r1->attack(*m_r2)) {
            emit battleFinished(m_i, m_j);
        } else if((att == 2 && m_r2->attack(*m_r1))) {
            emit battleFinished(m_j, m_i);
        }
    }
}
