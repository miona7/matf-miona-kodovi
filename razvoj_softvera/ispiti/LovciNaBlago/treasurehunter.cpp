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

QString TreasureHunter::toString() const {
    return m_name + ", brzina: " + QString::number(m_speed) + ", novcica: " + QString::number(m_numOfDucats);
}
