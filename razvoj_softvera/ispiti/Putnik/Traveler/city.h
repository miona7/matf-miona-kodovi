#ifndef CITY_H
#define CITY_H

#include <QString>
#include <QList>
#include <QVariant>
#include <QRandomGenerator>
#include <QMutex>

#include <iostream>

class City {
public:
    City() = default;
    City(const QVariant&);

    void fromQVariant(const QVariant&);
    QString toQString() const;
    QString getRandomArticle();
    unsigned distance(const City&) const;

    QString getName() const;
    unsigned getX() const;
    unsigned getY() const;
    QMutex* getMutex();

private:
    QString m_name;
    unsigned m_x;
    unsigned m_y;
    QList<QString> m_articles;
    QMutex m_mutex;

    unsigned absMinus(unsigned, unsigned) const;
};

#endif // CITY_H
