#include <cmath>

#include "grid.hpp"

Grid::Grid(size_t width, size_t height)
    : m_grid(height, std::vector<unsigned>(width, 0u))
{}

Grid* Grid::makeGrid(const std::vector<Line>& lines, bool fill_grid)
{
    if(lines.empty()){
        return new Grid(0u, 0u);
    }

    size_t width = 0u, height = 0u;
    for(auto& line : lines){
        auto p1 = line.getPoint1(), p2 = line.getPoint2();
        width = std::max<size_t>(width, std::max(p1.first, p2.first));
        height = std::max<size_t>(height, std::max(p1.second, p2.second));
    }

    Grid grid(width + 1u, height + 1u);

    if(fill_grid){
        grid.draw_line(lines);
    }

    auto grid_addr = &grid;
    return grid_addr;
}

void Grid::draw_line(const std::vector<Line>& lines)
{
    for(auto& line : lines){
        draw_line(line);
    }
}

void Grid::draw_line(
    unsigned x1, unsigned y1,
    unsigned x2, unsigned y2,
    unsigned val
)
{
    if(x1 == x2 && y1 == y2){
        set_point(x1, y1, val);
        return;
    }

    int delta_x = x2 - x1, delta_y = y2 - y1;
    int steps = std::max(delta_x, delta_y);

    float x_inc = delta_x / static_cast<float>(steps);
    float y_inc = delta_y / static_cast<float>(steps);

    float x = x1, y = y1;

    for (int i = 0; i <= steps; i++) {
        set_point(std::round(x), std::round(y), val);

        x += x_inc;
        y += y_inc;
    }
}

size_t Grid::getWidth() const
{
    return m_grid.empty() ? 0u : m_grid[0].size();
}

size_t Grid::getHeight() const
{
    return m_grid.size();
}

void Grid::set_point(unsigned x, unsigned y, unsigned val)
{
    m_grid[y][x] = val;
}

std::ostream& operator<<(std::ostream& out, const Grid& grid){
    for(auto& row : grid.m_grid){
        for(unsigned val : row){
            out << val << " ";
        }
        out << std::endl;
    }

    return out;
}