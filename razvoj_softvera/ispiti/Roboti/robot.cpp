#include "robot.h"

void Robot::fromQVariant(const QVariant& variant) {
    auto map = variant.toMap();
    m_name = map.value("name").toString();
    m_maxLifePoens = m_currLifePoens = map.value("hp").toUInt();

    auto atkList = map.value("atk").toList();
    m_minStrengthAttack = atkList[0].toUInt();
    m_minStrengthAttack = atkList[1].toUInt();
}

QString Robot::toQString() const {
    return m_name + " : hp=" + QString::number(m_maxLifePoens) + ", atk=[" +
           QString::number(m_minStrengthAttack) + "," + QString::number(m_maxStrengthAttack) + "]";
}

bool Robot::attack(Robot& target) const {
    return false;
}
