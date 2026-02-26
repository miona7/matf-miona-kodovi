#ifndef HUNTERWORKER_H
#define HUNTERWORKER_H

#include <QObject>
#include <QThread>
#include <QRandomGenerator>

#include "treasurehunter.h"
#include "treasuremap.h"

class HunterWorker : QThread {
    Q_OBJECT
public:
    HunterWorker(TreasureHunter*, TreasureMap*, double);

protected:
    void run() override;

private:
    TreasureHunter* m_hunter;
    TreasureMap* m_map;
    double m_gameSpeed;
};

#endif // HUNTERWORKER_H
