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
    QPair<unsigned, unsigned> getMapSize() const;
    TreasureMap::Tile getTileAt(const QPair<unsigned, unsigned>&) const;
    QList<QPair<unsigned, unsigned>> getMovableFrom(const QPair<unsigned, unsigned>&) const;

    bool grabTreasure(const QPair<unsigned, unsigned>&);
    bool hasDucats() const;

private:
    QList<QList<Tile>> m_tiles;
    unsigned m_numOfDucats;
};

#endif // TREASUREMAP_H
