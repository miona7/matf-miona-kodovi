#ifndef ROBOTWORKER_H
#define ROBOTWORKER_H

#include <QObject>
#include <QThread>
#include <QRandomGenerator>
#include <QMutex>
#include <QMutexLocker>

#include "robot.h"

class RobotWorker : public QThread {
    Q_OBJECT
public:
    RobotWorker(Robot*, Robot*, int, int);

signals:
    void battleFinished(int, int);

protected:
    void run() override;

private:
    Robot* m_r1;
    Robot* m_r2;
    int m_i;
    int m_j;
};

#endif // ROBOTWORKER_H
