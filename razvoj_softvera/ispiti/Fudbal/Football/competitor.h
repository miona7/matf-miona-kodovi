#ifndef COMPETITOR_H
#define COMPETITOR_H

#include <QString>
#include <QVariant>

class Competitor {
public:
    Competitor() = default;
    Competitor(const QVariant&);

    void fromQVariant(const QVariant&);
    QString toQString() const;

    QString getName() const;
    double getPrecision() const;
    void addPoints(unsigned);

private:
    QString m_name;
    QString m_club;
    double m_precision;
    unsigned m_points;
};

#endif // COMPETITOR_H
