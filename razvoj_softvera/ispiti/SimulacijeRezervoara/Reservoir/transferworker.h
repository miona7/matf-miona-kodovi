#ifndef TRANSFERWORKER_H
#define TRANSFERWORKER_H

#include <QObject>
#include <QThread>
#include <QMutex>
#include <QMutexLocker>
#include <QList>
#include <QRandomGenerator>

#include "source.h"

class TransferWorker : public QThread {
    Q_OBJECT
public:
    TransferWorker(QList<Source*>*, QMutex*);

signals:
    void sourceFinished(unsigned);

protected:
    void run() override;

private:
    QList<Source*>* m_sources;
    QMutex* m_mutex;
};

#endif // TRANSFERWORKER_H
