#include "source.h"

Source::Source(const QVariant& variant) {
    fromQVariant(variant);
}

void Source::fromQVariant(const QVariant& variant) {
    const auto map = variant.toMap();
    m_name = map["name"].toString();
    m_volume = map["volume"].toUInt();
}

QString Source::toQString() const {
    QString res = m_name + " - ";
    if(m_volume != 0) {
        res += QString::number(m_volume);
    } else {
        res += "izvor je iscrpljen";
    }

    return res;
}

unsigned Source::getVolume() const {
    return m_volume;
}

void Source::setVolume(unsigned volume) {
    m_volume = volume;
}
