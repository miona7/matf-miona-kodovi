#ifndef TREASUREHUNTER_H
#define TREASUREHUNTER_H

#include <QString>
#include <QVariant>
#include <QPair>

class TreasureHunter {
public:
    TreasureHunter() = default;
    TreasureHunter(const QVariant&);

    void fromQVariant(const QVariant&);
    QString toQString() const;
    QString getName() const;
    unsigned getSpeed() const;

    void setDucats(unsigned);
    unsigned getDucats() const;

    void addDucats(unsigned);

    QPair<unsigned, unsigned> getPosition() const;
    void setPosition(const QPair<unsigned, unsigned>&);

private:
    QString m_name;
    unsigned m_speed;
    unsigned m_numOfDucats;
    QPair<unsigned, unsigned> m_position;
};

#endif // TREASUREHUNTER_H
