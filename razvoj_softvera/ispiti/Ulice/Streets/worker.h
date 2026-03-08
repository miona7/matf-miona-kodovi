#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QThread>
#include <QRandomGenerator>
#include <QMutex>
#include <QMutexLocker>

#include "street.h"

class Worker : public QThread {
    Q_OBJECT
public:
    Worker(Street*, unsigned);

signals:
    void finishedNormally(Street*, unsigned, bool);
    void removed(Street*, unsigned, unsigned);

protected:
    void run();

private:
    Street* m_street;
    unsigned m_id;
};

#endif // WORKER_H
