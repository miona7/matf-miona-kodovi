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

    void fromQVariant(const QVariant&);
    QPair<int, int> getMapSize() const;
    TreasureMap::Tile getTileAt(const QPair<int, int>&) const;

private:
    QList<QList<Tile>> m_tiles;
};

#endif // TREASUREMAP_H
