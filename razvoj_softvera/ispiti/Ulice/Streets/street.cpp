#include "street.h"

Street::Street(const QVariant& variant) {
    fromQVariant(variant);
}

void Street::fromQVariant(const QVariant& variant) {
    auto map = variant.toMap();
    m_name = map["name"].toString();
    m_height = map["poleHeight"].toUInt();

    auto list = map["decorations"].toList();
    for(auto d : list) {
        m_numOfCurrDecorations.append(d.toUInt());
    }
}

QString Street::toQString() const {
    auto res = "Ulica " + m_name + ", dekoracije [";
    for(auto i = 0; i < m_numOfCurrDecorations.size(); i++) {
        res += QString::number(m_numOfCurrDecorations[i]);
        if(i != m_numOfCurrDecorations.size() - 1) {
            res += ", ";
        }
    }
    res += "]";
    return res;
}

int Street::getDecoratedLamppost() const {
    bool hasDecoration = false;
    for(auto d : m_numOfCurrDecorations) {
        if(d != 0) {
            hasDecoration = true;
            break;
        }
    }

    if(!hasDecoration) {
        return -1;
    }

    while(true) {
        auto index = static_cast<int>(QRandomGenerator::global()->bounded(m_numOfCurrDecorations.size()));
        auto tmp = m_numOfCurrDecorations[index];
        if(tmp != 0) {
            return index;
        }
    }
}
