#include "transferworker.h"

TransferWorker::TransferWorker(QList<Source*>* sources, QMutex* mutex) : m_sources(sources), m_mutex(mutex) {
}

void TransferWorker::run() {
    QThread::msleep(QRandomGenerator::global()->bounded(500, 1001));

    while(true) {
        QMutexLocker lock(m_mutex);

        auto* source = (*m_sources)[QRandomGenerator::global()->bounded(m_sources->size())];
        const auto v = QRandomGenerator::global()->bounded(100, 201);

        const auto currVolume = source->getVolume();
        if(currVolume != 0) {
            if(currVolume <= v) {
                source->setVolume(0);
                emit sourceFinished(currVolume);
                break;
            } else {
                source->setVolume(currVolume - v);
                emit sourceFinished(v);
            }
        }
    }
}
