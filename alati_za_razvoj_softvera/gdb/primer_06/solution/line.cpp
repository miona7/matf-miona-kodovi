#include <sstream>
#include <fstream>

#include "line.hpp"

namespace
{
    const std::string extension = ".lines";
}

Line::Line(const point_t& p1, const point_t& p2, unsigned value)
    : m_p1(p1), m_p2(p2), m_value(value)
{}

Line::Line(std::string str_line)
{
    unsigned x1, y1, x2, y2;
    std::istringstream str_in(str_line);
    str_in >> x1 >> y1 >> x2 >> y2 >> m_value;
    m_p1 = std::make_pair(x1, y1);
    m_p2 = std::make_pair(x2, y2);
}

std::vector<Line> Line::readLines(std::string file_path)
{
    std::vector<Line> result;
    std::string str_line;
    
    if(file_path.find(extension) == std::string::npos) {
        file_path += extension;
    }

    std::ifstream infile(file_path);
    
    while (std::getline(infile, str_line))
    {
        result.emplace_back(Line(str_line));
    }

    return result;
}