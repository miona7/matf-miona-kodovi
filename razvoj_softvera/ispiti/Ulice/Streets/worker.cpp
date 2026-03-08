#include "worker.h"

Worker::Worker(Street* street, unsigned id) : m_street(street), m_id(id) {
}

void Worker::run() {
    unsigned h = m_street->getHeight();
    QThread::msleep(QRandomGenerator::global()->bounded(1000, 1501) * h / 10);

    while(true) {
        QMutexLocker lock(m_street->getMutex());
        int index = m_street->getDecoratedLamppost();
        if(index == -1) {
            emit finishedNormally(m_street, m_id, true);
            break;
        }

        double p = QRandomGenerator::global()->generateDouble();
        if(p <= 0.1) {
            emit finishedNormally(m_street, m_id, false);
            break;
        }

        unsigned numOfDecor = QRandomGenerator::global()->bounded(1, 11);
        m_street->setDecorations(index, numOfDecor);
        emit removed(m_street, m_id, numOfDecor);
    }
}
