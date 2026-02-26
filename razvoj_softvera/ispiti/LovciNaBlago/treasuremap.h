#ifndef TREASUREMAP_H
#define TREASUREMAP_H

#include <QPair>
#include <QList>
#include <QVariant>

#include <exception>

class TreasureMap {
public:
    enum class Tile { Clear, Wall, Treasure };

    TreasureMap() = default;
    TreasureMap(const QVariant&);

    void fromQVariant(const QVariant&);

private:
    QList<QList<Tile>> m_tiles;
};

#endif // TREASUREMAP_H
