#ifndef TREASUREHUNTER_H
#define TREASUREHUNTER_H

#include <QString>
#include <QVariant>

class TreasureHunter {
public:
    TreasureHunter() = default;
    TreasureHunter(const QVariant&);

    void fromQVariant(const QVariant&);
    QString toString() const;

private:
    QString m_name;
    unsigned m_speed;
    unsigned m_numOfDucats;
    std::pair<unsigned, unsigned> m_position;
};

#endif // TREASUREHUNTER_H
