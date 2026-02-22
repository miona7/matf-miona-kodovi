#include <utility>
#include <vector>
#include <string>

using point_t = std::pair<unsigned, unsigned>;

class Line {
public:
    Line(const point_t& p1, const point_t& p2, unsigned value);
    Line(std::string str_line);

    static std::vector<Line> readLines(std::string file_path);

    inline point_t getPoint1() const {return m_p1;}
    inline point_t getPoint2() const {return m_p2;}
    inline unsigned getValue() const {return m_value;}
private:
    point_t m_p1;
    point_t m_p2;
    unsigned m_value;
};