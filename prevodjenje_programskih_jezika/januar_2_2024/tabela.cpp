#include "tabela.hpp"

TabelaSimbola::TabelaSimbola() {}

void TabelaSimbola::Ispisi(std::ostream& s) const {
    for(auto it : _promenljive) {
        s << it.first << ": " << it.second << std::endl;
    }
}

void TabelaSimbola::DefinisiPromenljivu(const std::string& id, const std::string& v) {
    if(_promenljive.find(id) != _promenljive.end()) {
        throw std::invalid_argument("promenjiva je vec definisana");
    }
    _promenljive[id] = v;
}

void TabelaSimbola::DodeliVrednost(const std::string& id, const std::string& v) {
    if(_promenljive.find(id) == _promenljive.end()) {
        throw std::invalid_argument("promenjiva nije definisana");
    }
    _promenljive[id] = v;
}

std::string TabelaSimbola::VrednostPromelnjive(const std::string& id) const {
    auto it = _promenljive.find(id);
    if(it == _promenljive.end()) {
        throw std::invalid_argument("promenjiva nije definisana");
    }
    return it->second;
}

std::ostream& operator<<(std::ostream& s, const TabelaSimbola& ts) {
    ts.Ispisi(s);
    return s;
}
