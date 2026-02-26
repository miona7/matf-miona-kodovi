#include "treasurehunter.h"

TreasureHunter::TreasureHunter(const QVariant& variant) {
    fromQVariant(variant);
}

void TreasureHunter::fromQVariant(const QVariant& variant) {
    auto map = variant.toMap();

    m_name = map["ime"].toString();
    m_speed = map["brzina"].toUInt();
    m_numOfDucats = 0;

    unsigned row = map["red"].toUInt();
    unsigned column = map["kolona"].toUInt();

    m_position = {row, column};
}

QString TreasureHunter::toQString() const {
    return m_name + ", brzina: " + QString::number(m_speed) + ", novcica: " + QString::number(m_numOfDucats);
}

unsigned TreasureHunter::getSpeed() const {
    return m_speed;
}

void TreasureHunter::addDucats(unsigned ducats) {
    m_numOfDucats += ducats;
}

QPair<unsigned, unsigned> TreasureHunter::getPosition() const {
    return m_position;
}

void TreasureHunter::setPosition(const QPair<unsigned, unsigned>& pos) {
    m_position = pos;
}
