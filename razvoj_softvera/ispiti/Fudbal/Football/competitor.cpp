#include "competitor.h"

Competitor::Competitor(const QVariant& variant) {
    fromQVariant(variant);
}

void Competitor::fromQVariant(const QVariant& variant) {
    const auto map = variant.toMap();
    m_name = map["ime"].toString();
    m_precision = map["preciznost"].toDouble();
    m_points = 0;

    if(map.find("klub") != map.end()) {
        m_club = map["klub"].toString();
    } else {
        m_club = "amater";
    }
}

QString Competitor::toQString() const {
    return m_name + ", " + m_club + ", " + QString::number(m_points);
}

QString Competitor::getName() const {
    return m_name;
}

double Competitor::getPrecision() const {
    return m_precision;
}

void Competitor::addPoints(unsigned points) {
    m_points += points;
}
