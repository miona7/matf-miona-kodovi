#include "robot.h"

Robot::Robot(const QVariant& variant) {
    fromQVariant(variant);
}

void Robot::fromQVariant(const QVariant& variant) {
    auto map = variant.toMap();
    m_name = map.value("name").toString();
    m_maxLifePoints = m_currLifePoints = map.value("hp").toUInt();

    auto atkList = map.value("atk").toList();
    m_minStrengthAttack = atkList[0].toUInt();
    m_minStrengthAttack = atkList[1].toUInt();
}

QString Robot::toQString() const {
    return m_name + " : hp=" + QString::number(m_maxLifePoints) + ", atk=[" +
           QString::number(m_minStrengthAttack) + "," + QString::number(m_maxStrengthAttack) + "]";
}

bool Robot::attack(Robot& target) const {
    unsigned damage = QRandomGenerator::global()->bounded(m_minStrengthAttack, m_maxStrengthAttack + 1);
    double scaling = std::max(0.5, static_cast<double>(m_currLifePoints) / m_maxLifePoints);
    unsigned scaledDamage = scaling * damage;

    if(scaledDamage >= target.getCurrLifePoints()) {
        target.setCurrLifePoints(0);
    } else {
        target.setCurrLifePoints(target.getCurrLifePoints() - scaledDamage);
    }

    return target.isDead();
}

bool Robot::isDead() const {
    return m_currLifePoints == 0;
}

unsigned Robot::getCurrLifePoints() const {
    return m_currLifePoints;
}

void Robot::setCurrLifePoints(unsigned points) {
    m_currLifePoints = points;
}
