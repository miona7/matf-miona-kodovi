#ifndef HUNTERWORKER_H
#define HUNTERWORKER_H

#include <QObject>
#include <QThread>
#include <QRandomGenerator>
#include <QList>
#include <QMutex>
#include <QMutexLocker>

#include "treasurehunter.h"
#include "treasuremap.h"

class HunterWorker : public QThread {
    Q_OBJECT
public:
    HunterWorker(QList<TreasureHunter*>*, unsigned, QMutex*, TreasureMap*, double);

signals:
    void hunterMoved(QPair<unsigned, unsigned>, QPair<unsigned, unsigned>);
    void hunterFoundTreasure(unsigned);

protected:
    void run() override;

private:
    QList<TreasureHunter*>* m_hunters;
    unsigned m_index;
    QMutex* m_mutex;
    TreasureMap* m_map;
    double m_gameSpeed;
};

#endif // HUNTERWORKER_H
