#include "singer.h"

Singer::Singer(const QVariant& variant) {
    fromQVariant(variant);
}

void Singer::fromQVariant(const QVariant& variant) {
    auto map = variant.toMap();
    m_name = map["name"].toString();
    m_points = map["points"].toUInt();
}

QString Singer::toQString() const {
    return m_name + ": " + QString::number(m_points);
}

void Singer::addPoints(unsigned points) {
    m_points += points;
}

QString Singer::getName() const {
    return m_name;
}

unsigned Singer::getPoints() const {
    return m_points;
}

QMutex* Singer::getMutex() {
    return &m_mutex;
}
