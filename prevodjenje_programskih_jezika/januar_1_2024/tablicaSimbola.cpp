#include "tablicaSimbola.hpp"

TablicaSimbola::TablicaSimbola() {} 

void TablicaSimbola::DefinisiPromenljivu(const std::string& s, int vr = 0) {
    if(_promenljive.find(s) != _promenljive.end()) {
        throw std::invalid_argument("promenljiva je deklarisana");
    }
    _promenljive[s] = vr;
}

void TablicaSimbola::DodeliVrednost(const std::string& s, int vr) {
    if(_promenljive.find(s) == _promenljive.end()) {
        throw std::invalid_argument("promenljiva nije deklarisana");
    }
    _promenljive[s] = vr;
}

int TablicaSimbola::VrednostPromenljive(const std::string& s) const {
    auto it = _promenljive.find(s);
    if(it == _promenljive.end()) {
        throw std::invalid_argument("promenljiva nije deklarisana");
    }
    return it->second;
}
