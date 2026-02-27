#ifndef TRAVELERWORKER_H
#define TRAVELERWORKER_H

#include <QObject>
#include <QThread>
#include <QRandomGenerator>
#include <QString>
#include <QList>
#include <QMutex>
#include <QMutexLocker>

#include "city.h"

class TravelerWorker : public QThread {
    Q_OBJECT
public:
    TravelerWorker(QList<City*>*);

signals:
    void tookArticle(const QString&);
    void menhetnDistance(unsigned);

protected:
    void run() override;

private:
    City* m_currCity;
    QList<City*>* m_cities;
    unsigned m_distance;
};

#endif // TRAVELERWORKER_H
