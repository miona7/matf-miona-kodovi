#include "text.hpp"

#include <fstream>
#include <streambuf>

namespace {
    std::vector<words_t>* load_replacements(const std::string& filename){
        std::vector<words_t> result;
        auto result_ptr = &result;
        
        Text words_file = Text::fromFile(filename);
        for (auto& line : words_file.split('\n')){
            result_ptr->push_back(Text(line).split('-'));
        }
        
        return result_ptr;
    }
}

Text::Text(const std::string& s) : m_text(s) {
    trim();
}

Text Text::fromFile(const std::string& filepath) {
    std::ifstream t(filepath);
    return Text(std::string(
        std::istreambuf_iterator<char>(t),
        std::istreambuf_iterator<char>()
    ));
}

unsigned Text::find_and_replace(const word_t& word, const word_t& replacement) {
    if (word.empty() || m_text.empty()) return 0u;

    std::string result;
    size_t startPos = 0;
    size_t endPos = m_text.find(word);

    unsigned count(0u);

    while (endPos != std::string::npos) {
        result += m_text.substr(startPos, endPos - startPos);
        startPos = endPos + word.length();
        endPos = m_text.find(word, startPos);
        ++count;
    }

    result += m_text.substr(startPos);

    m_text = result;

    return count;
}

unsigned Text::find_and_replace(const words_t& words, const word_t& replacement) {
    unsigned count(0u);

    for (auto& word : words){
        count += find_and_replace(word, replacement);
    }

    return count;
}

unsigned Text::find_and_replace(const std::string& filepath){
    unsigned count(0u);
    auto replacements = load_replacements(filepath);

    for (auto& replacement : *replacements){
        auto replacement_word = replacement[replacement.size() - 1];
        replacement.pop_back();
        count += find_and_replace(replacement, replacement_word);
    }

    trim();
    return count;
}

words_t Text::split(const char delimiter) const
{
    words_t result;
    std::string temp_str;
    for(auto c : m_text){
        if(c == delimiter){
            if(!temp_str.empty()){
                result.push_back(Text(temp_str).text());
                temp_str.clear();
            }
        }
        else{
            temp_str.push_back(c);
        }
    }
    if(!temp_str.empty())
        result.push_back(Text(temp_str).text());

    return result;
}


void Text::trim() {
    size_t startPos = 0;
    size_t endPos = m_text.length() - 1;

    for (; startPos <= endPos && std::isspace(m_text[startPos]); ++startPos);

    if (startPos <= endPos) {
        m_text = m_text.substr(startPos, endPos - startPos + 1);
    }
    else {
        m_text.clear();
    }
}

std::ostream& operator<<(std::ostream& out, const Text& text){
    return out << text.text();
}