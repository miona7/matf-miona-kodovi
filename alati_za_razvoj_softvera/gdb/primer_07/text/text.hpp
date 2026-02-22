#ifndef __TEXT_HPP__
#define __TEXT_HPP__

#include <iostream>
#include <vector>

using word_t = std::string;
using words_t = std::vector<word_t>;

class Text {
public:
    explicit Text(const std::string& s);
    static Text fromFile(const std::string& filepath);

    inline std::string text() const {return m_text;}

    unsigned find_and_replace(const word_t& word, const word_t& replacement);
    unsigned find_and_replace(const words_t& words, const word_t& replacement);
    unsigned find_and_replace(const std::string& filepath);

    words_t split(char delimiter) const;
    void trim();

private:
    std::string m_text;
};

std::ostream& operator<<(std::ostream&, const Text&);

#endif


