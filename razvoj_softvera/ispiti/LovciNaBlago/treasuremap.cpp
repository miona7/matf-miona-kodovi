#include "treasuremap.h"

namespace {
    TreasureMap::Tile numToTile(int num) {
        switch(num) {
        case 0:
            return TreasureMap::Tile::Clear;
        case 1:
            return TreasureMap::Tile::Wall;
        case 2:
            return TreasureMap::Tile::Treasure;
        default:
            throw std::invalid_argument("invalid number for tile");
        }
    }
}

void TreasureMap::fromQVariant(const QVariant& variant) {
    m_tiles.clear();

    const auto rowList = variant.toList();
    for(int i = 0; i < rowList.size(); i++) {
        m_tiles.push_back(QList<Tile>());
        const auto row = rowList[i].toList();
        for(const auto& numVar : row) {
            const auto tile = numToTile(numVar.toInt());
            m_tiles[i].push_back(tile);
        }
    }
}

QPair<int, int> TreasureMap::getMapSize() const {
    if(m_tiles.isEmpty()) {
        return {0, 0};
    }
    return {m_tiles.size(), m_tiles[0].size()};
}

TreasureMap::Tile TreasureMap::getTileAt(const QPair<int, int>& pos) const {
    return m_tiles[pos.first][pos.second];
}
