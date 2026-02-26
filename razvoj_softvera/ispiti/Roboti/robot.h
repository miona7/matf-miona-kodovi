#ifndef ROBOT_H
#define ROBOT_H

#include <QString>
#include <QVariant>
#include <QRandomGenerator>
#include <QMutex>

class Robot {
public:
    Robot() = default;
    Robot(const QVariant&);

    void fromQVariant(const QVariant&);
    QString toQString() const;
    bool attack(Robot&) const;

    bool isDead() const;

    unsigned getMaxLifePoints() const;

    unsigned getCurrLifePoints() const;
    void setCurrLifePoints(unsigned);

    QMutex* getBattleMutex();
    QString getName() const;

private:
    QString m_name;
    unsigned m_minStrengthAttack;
    unsigned m_maxStrengthAttack;
    unsigned m_maxLifePoints;
    unsigned m_currLifePoints;
    QMutex m_battleMutex;
};

#endif // ROBOT_H
