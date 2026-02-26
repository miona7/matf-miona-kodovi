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

private:
    QString m_name;
    unsigned m_speed;
    unsigned m_numOfDucats;
    QPair<unsigned, unsigned> m_position;
};

#endif // TREASUREHUNTER_H
