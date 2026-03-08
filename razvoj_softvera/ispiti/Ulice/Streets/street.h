#ifndef STREET_H
#define STREET_H

#include <QString>
#include <QList>
#include <QVariant>
#include <QRandomGenerator>
#include <QMutex>

class Street {
public:
    Street() = default;
    Street(const QVariant&);

    void fromQVariant(const QVariant&);
    QString toQString() const;
    int getDecoratedLamppost() const;

    void setDecorations(int, unsigned);

    QString getName() const;
    unsigned getHeight() const;
    QMutex* getMutex();

private:
    QString m_name;
    unsigned m_height;
    QList<unsigned> m_numOfCurrDecorations;
    unsigned m_initNumOfDecorations;
    QMutex m_mutex;
};

#endif // STREET_H
