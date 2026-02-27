#include "city.h"

City::City(const QVariant& variant) {
    fromQVariant(variant);
}

void City::fromQVariant(const QVariant& variant) {
    auto map = variant.toMap();

    m_name = map["name"].toString();

    auto coordinates = map["coordinates"].toList();
    m_x = coordinates[0].toUInt();
    m_y = coordinates[1].toUInt();

    auto articles = map["articles"].toList();
    for(const auto& a : articles) {
        m_articles.append(a.toString());
    }
}

QString City::toQString() const {
    return m_name + " (" + QString::number(m_x) + "," + QString::number(m_y) + "): Broj artikala = " + QString::number(m_articles.size());
}

QString City::getRandomArticle() {
    if(m_articles.empty()) {
        return "";
    }
    auto article = m_articles[static_cast<unsigned>(QRandomGenerator::global()->bounded(m_articles.size()))];

    m_articles.removeIf([&article](const auto& a) { return article == a; });

    return article;
}

unsigned City::distance(const City& city) const {
    return absMinus(m_x, city.getX()) + absMinus(m_y, city.getY());
}

QString City::getName() const {
    return m_name;
}

unsigned City::getX() const {
    return m_x;
}

unsigned City::getY() const {
    return m_y;
}

QMutex* City::getMutex() {
    return &m_mutex;
}

unsigned City::absMinus(unsigned a, unsigned b) const {
    return a >= b ? a - b : b - a;
}
