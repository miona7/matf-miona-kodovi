#ifndef ROBOT_H
#define ROBOT_H

#include <QString>
#include <QVariant>
#include <QRandomGenerator>

class Robot {
public:
    Robot() = default;

    void fromQVariant(const QVariant&);
    QString toQString() const;
    bool attack(Robot&) const;

private:
    QString m_name;
    unsigned m_minStrengthAttack;
    unsigned m_maxStrengthAttack;
    unsigned m_maxLifePoens;
    unsigned m_currLifePoens;
};

#endif // ROBOT_H
