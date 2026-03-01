#ifndef SOURCE_H
#define SOURCE_H

#include <QString>
#include <QVariant>

class Source {
public:
    Source() = default;
    Source(const QVariant&);

    void fromQVariant(const QVariant&);
    QString toQString() const;

    unsigned getVolume() const;
    void setVolume(unsigned);

private:
    QString m_name;
    unsigned m_volume;
};

#endif // SOURCE_H
