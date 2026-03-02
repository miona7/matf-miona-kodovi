#ifndef COMPETITORWORKER_H
#define COMPETITORWORKER_H

#include <QObject>
#include <QThread>
#include <QList>
#include <QRandomGenerator>

#include "competitor.h"

class CompetitorWorker : public QThread {
    Q_OBJECT
public:
    CompetitorWorker(QList<Competitor*>*, unsigned, unsigned);

signals:
    void goal(bool, unsigned);

protected:
    void run() override;

private:
    QList<Competitor*>* m_competitors;
    unsigned m_index;
    unsigned m_numOfTries;
};

#endif // COMPETITORWORKER_H
