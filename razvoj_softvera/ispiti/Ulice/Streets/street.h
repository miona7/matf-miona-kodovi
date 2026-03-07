#ifndef STREET_H
#define STREET_H

#include <QString>
#include <QList>
#include <QVariant>
#include <QRandomGenerator>

class Street {
public:
    Street() = default;
    Street(const QVariant&);

    void fromQVariant(const QVariant&);
    QString toQString() const;
    int getDecoratedLamppost() const;

private:
    QString m_name;
    unsigned m_height;
    QList<unsigned> m_numOfCurrDecorations;
    unsigned m_initNumOfDecorations;
};

#endif // STREET_H
