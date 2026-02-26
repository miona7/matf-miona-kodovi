#ifndef ROBOT_H
#define ROBOT_H

#include <QString>
#include <QVariant>
#include <QRandomGenerator>

class Robot {
public:
    Robot() = default;
    Robot(const QVariant&);

    void fromQVariant(const QVariant&);
    QString toQString() const;
    bool attack(Robot&) const;

    bool isDead() const;

    unsigned getCurrLifePoints() const;
    void setCurrLifePoints(unsigned);

private:
    QString m_name;
    unsigned m_minStrengthAttack;
    unsigned m_maxStrengthAttack;
    unsigned m_maxLifePoints;
    unsigned m_currLifePoints;
};

#endif // ROBOT_H
