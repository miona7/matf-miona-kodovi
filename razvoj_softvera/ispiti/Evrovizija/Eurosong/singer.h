#ifndef SINGER_H
#define SINGER_H

#include <QString>
#include <QVariant>
#include <QMutex>

class Singer {
public:
    Singer() = default;
    Singer(const QVariant&);

    void fromQVariant(const QVariant&);
    QString toQString() const;

    void addPoints(unsigned);
    QString getName() const;
    unsigned getPoints() const;
    QMutex* getMutex();

private:
    QString m_name;
    unsigned m_points;
    QMutex m_mutex;
};

#endif // SINGER_H
