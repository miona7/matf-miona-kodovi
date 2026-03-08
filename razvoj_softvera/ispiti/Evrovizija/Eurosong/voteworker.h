#ifndef VOTEWORKER_H
#define VOTEWORKER_H

#include <QObject>
#include <QThread>
#include <QList>
#include <QSet>
#include <QString>
#include <QRandomGenerator>
#include <QMutexLocker>

#include "singer.h"

class VoteWorker : public QThread {
    Q_OBJECT
public:
    VoteWorker(Singer*, QList<Singer*>*);

signals:
    void voted();

protected:
    void run();

private:
    Singer* m_singer;
    QList<Singer*>* m_singers;
    QSet<QString> m_countries;
};

#endif // VOTEWORKER_H
