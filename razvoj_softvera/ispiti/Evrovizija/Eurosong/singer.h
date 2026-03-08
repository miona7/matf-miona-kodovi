#ifndef SINGER_H
#define SINGER_H

#include "QString"
#include "QVariant"

class Singer {
public:
    Singer() = default;
    Singer(const QVariant&);

    void fromQVariant(const QVariant&);
    QString toQString() const;

private:
    QString m_name;
    unsigned m_points;
};

#endif // SINGER_H
