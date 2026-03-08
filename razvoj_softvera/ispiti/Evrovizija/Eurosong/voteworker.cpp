#include "voteworker.h"

VoteWorker::VoteWorker(Singer* singer, QList<Singer*>* singers) : m_singer(singer), m_singers(singers) {}

void VoteWorker::run() {
    for(unsigned i = 1; i <= 12; i++) {
        while(true) {
            auto* countrie = (*m_singers)[QRandomGenerator::global()->bounded(m_singers->size())];
            auto name = countrie->getName();
            if(m_countries.find(name) == m_countries.end() && name != m_singer->getName()) {
                m_countries.insert(name);
                QMutexLocker lock(countrie->getMutex());
                countrie->addPoints(i);
                emit voted();
                break;
            }
        }
        QThread::msleep(1000);
    }
}
