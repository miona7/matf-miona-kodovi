#include <iostream>

#include "line.hpp"

class Grid {
public:
    Grid(size_t width, size_t height);

    static Grid* makeGrid(const std::vector<Line>&, bool fill_grid = true);

    void draw_line(const std::vector<Line>& lines);

    inline void draw_line(const Line& line)
    {
        draw_line(line.getPoint1(), line.getPoint2(), line.getValue());
    }

    inline void draw_line(const point_t& p1, const point_t& p2, unsigned value)
    {
        draw_line(
            p1.first, p1.second,
            p2.first, p2.second,
            value
        );
    }

    void draw_line(
        unsigned x1, unsigned y1,
        unsigned x2, unsigned y2,
        unsigned val
    );

    size_t getWidth() const;
    size_t getHeight() const;

private:
    std::vector<std::vector<unsigned>> m_grid;

    void set_point(unsigned x, unsigned y, unsigned val);
    friend std::ostream& operator<<(std::ostream& out, const Grid& grid);
};

std::ostream& operator<<(std::ostream& out, const Grid& grid);