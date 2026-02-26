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
    m_numOfDucats = 0;

    const auto rowList = variant.toList();
    for(int i = 0; i < rowList.size(); i++) {
        m_tiles.push_back(QList<Tile>());
        const auto row = rowList[i].toList();
        for(const auto& numVar : row) {
            const auto tile = numToTile(numVar.toInt());
            m_tiles[i].push_back(tile);
            if(tile == TreasureMap::Tile::Treasure) {
                m_numOfDucats++;
            }
        }
    }
}

QPair<unsigned, unsigned> TreasureMap::getMapSize() const {
    if(m_tiles.isEmpty()) {
        return {0, 0};
    }
    return {m_tiles.size(), m_tiles[0].size()};
}

TreasureMap::Tile TreasureMap::getTileAt(const QPair<unsigned, unsigned>& pos) const {
    return m_tiles[pos.first][pos.second];
}

QList<QPair<unsigned, unsigned>> TreasureMap::getMovableFrom(const QPair<unsigned, unsigned>& pos) const {
    QList<QPair<unsigned, unsigned>> positions;
    const auto [row, column] = pos;

    if(row > 0 && m_tiles[row - 1][column] != TreasureMap::Tile::Wall) {
        positions.append({row - 1, column});
    }
    if(row < m_tiles.size() && m_tiles[row + 1][column] != TreasureMap::Tile::Wall) {
        positions.append({row + 1, column});
    }
    if(column > 0 && m_tiles[row][column - 1] != TreasureMap::Tile::Wall) {
        positions.append({row, column - 1});
    }
    if(column < m_tiles[row].size() && m_tiles[row][column + 1] != TreasureMap::Tile::Wall) {
        positions.append({row, column + 1});
    }

    return positions;
}

bool TreasureMap::grabTreasure(const QPair<unsigned, unsigned>& pos) {
    if(m_tiles[pos.first][pos.second] == TreasureMap::Tile::Treasure) {
        m_tiles[pos.first][pos.second] = TreasureMap::Tile::Clear;
        m_numOfDucats--;
        return true;
    }
    return false;
}

bool TreasureMap::hasDucats() const {
    return m_numOfDucats != 0;
}

