#include "stablo.hpp"

ASTCvor::~ASTCvor() {}

std::ostream& operator<<(std::ostream& s, const ASTCvor& c) {
    c.Ispisi(s);
    return s;
}

/**************************************************************/

NizNaredbi::NizNaredbi() {}

NizNaredbi::NizNaredbi(const NizNaredbi& nn) {
    for(size_t i = 0; i < nn._naredbe.size(); i++) {
        _naredbe.push_back(nn._naredbe[i]->Kloniraj());
    }
}

NizNaredbi::~NizNaredbi() {
    for(size_t i = 0; i < _naredbe.size(); i++) {
        delete _naredbe[i];
    }
}

void NizNaredbi::DodajNaredbu(ASTCvor* n) {
    _naredbe.push_back(n);
}

int NizNaredbi::Interpretiraj(TablicaSimbola& ts) const {
    for(size_t i = 0; i < _naredbe.size(); i++) {
        _naredbe[i]->Interpretiraj(ts);
        std::cout << std::endl;
    }
    return 0;
} 

void NizNaredbi::Ispisi(std::ostream& s) const {
    for(size_t i = 0; i < _naredbe.size(); i++) {
        s << *_naredbe[i] << ';' << std::endl;
    }
}

ASTCvor* NizNaredbi::Kloniraj() const {
    return new NizNaredbi(*this);
}

/**************************************************************/

Deklaracija::Deklaracija(const std::string& s) : _id(s) {}

int Deklaracija::Interpretiraj(TablicaSimbola& ts) const {
    ts.DefinisiPromenljivu(_id, 0);
    return 0;
} 

void Deklaracija::Ispisi(std::ostream& s) const {
    s << "def " << _id;
}

ASTCvor* Deklaracija::Kloniraj() const {
    return new Deklaracija(*this);
}

/**************************************************************/

Definicija::Definicija(const std::string& s, ASTCvor* i) : _id(s), _izraz(i) {}

Definicija::Definicija(const Definicija& d) : _id(d._id), _izraz(d._izraz->Kloniraj()) {}

Definicija::~Definicija() {
    delete _izraz;
}

int Definicija::Interpretiraj(TablicaSimbola& ts) const {
    ts.DefinisiPromenljivu(_id, _izraz->Interpretiraj(ts));
    return 0;
} 

void Definicija::Ispisi(std::ostream& s) const {
    s << "def " << _id << " = " << *_izraz;
}

ASTCvor* Definicija::Kloniraj() const {
    return new Definicija(*this);
}

/***********************************************************************/

Dodela::Dodela(const std::string& s, ASTCvor* i) : _id(s), _izraz(i) {}

Dodela::Dodela(const Dodela& d) : _id(d._id), _izraz(d._izraz->Kloniraj()) {}

Dodela::~Dodela() {
    delete _izraz;
}

int Dodela::Interpretiraj(TablicaSimbola& ts) const {
    ts.DodeliVrednost(_id, _izraz->Interpretiraj(ts));
    return 0;
}

void Dodela::Ispisi(std::ostream& s) const {
    s << _id << " = " << *_izraz;
}

ASTCvor* Dodela::Kloniraj() const {
    return new Dodela(*this);
}

/***********************************************************************/

Ispis::Ispis(char c, ASTCvor* i) : _format(c), _izraz(i), _logicka(false) {}

Ispis::Ispis(ASTCvor* i) : _izraz(i), _logicka(true) {}

Ispis::Ispis(const Ispis& i) : _format(i._format), _izraz(i._izraz->Kloniraj()), _logicka(i._logicka) {}

Ispis::~Ispis() {
    delete _izraz;
}

int Ispis::Interpretiraj(TablicaSimbola& ts) const {
    if(!_logicka) {
        if(_format == 'b') {
            std::cout << std::bitset<8*sizeof(int)>(_izraz->Interpretiraj(ts));
        } else if(_format == 'h') {
            std::cout << std::hex << _izraz->Interpretiraj(ts) << std::dec;
        } else if (_format == 'd') {
            std::cout << _izraz->Interpretiraj(ts);
        } else {
            throw std::invalid_argument("nedozvoljen format");
        }
    } else {
        std::cout << (_izraz->Interpretiraj(ts) ? "True" : "False");
    }
    return 0;
}

void Ispis::Ispisi(std::ostream& s) const {
    if(!_logicka) {
        s << "print(\"%" << _format << "\", " << *_izraz << ")";
    } else {
        s << *_izraz;
    }
}

ASTCvor* Ispis::Kloniraj() const {
    return new Ispis(*this);
}

/**************************************************************/

BinarnaOperacija::BinarnaOperacija(const std::string& op, ASTCvor* levi, ASTCvor* desni)
    : _op(op), _levi(levi), _desni(desni) {}

BinarnaOperacija::BinarnaOperacija(const BinarnaOperacija& bo)
    : _op(bo._op), _levi(bo._levi->Kloniraj()), _desni(bo._desni->Kloniraj()) {}

BinarnaOperacija::~BinarnaOperacija() {
    delete _levi;
    delete _desni;
}

int BinarnaOperacija::Interpretiraj(TablicaSimbola& ts) const {
    int l = _levi->Interpretiraj(ts);
    int d = _desni->Interpretiraj(ts);

    if(_op == "+") {
        return l + d;
    } else if(_op == "-") {
        return l - d;
    } else if(_op == "*") {
        return l * d;
    } else if(_op == "/") {
        if(d == 0) {
            throw std::invalid_argument("deljenje nulom");
        }
        return l / d;
    } else if(_op == "%") {
        if(d == 0) {
            throw std::invalid_argument("deljenje nulom");
        }
        return l % d;
    } else if(_op == "&") {
        return l & d;
    } else if(_op == "|") {
        return l | d;
    } else if(_op == "^") {
        return l ^ d;
    } else if(_op == "<") {
        return l < d;
    } else if(_op == ">") {
        return l > d;
    } else if(_op == "<=") {
        return l <= d;
    } else if(_op == ">=") {
        return l >= d;
    } else if(_op == "==") {
        return l == d;
    } else if(_op == "!=") {
        return l != d;
    } else {
        throw std::invalid_argument("nedozvoljen operator");
    }
} 

void BinarnaOperacija::Ispisi(std::ostream& s) const {
    s << *_levi;
    if(_op == "+") {
        s << " + ";
    } else if(_op == "-") {
        s << " - ";
    } else if(_op == "*") {
        s << " * ";
    } else if(_op == "/") {
        s << " / ";
    } else if(_op == "%") {
        s << " % ";
    } else if(_op == "&") {
        s << " & ";
    } else if(_op == "|") {
        s << " | ";
    } else if(_op == "^") {
        s << " ^ ";
    } else if(_op == "<") {
        s << " < ";
    } else if(_op == ">") {
        s << " > ";
    } else if(_op == "<=") {
        s << " <= ";
    } else if(_op == ">=") {
        s << " >= ";
    } else if(_op == "==") {
        s << " == ";
    } else if(_op == "!=") {
        s << " != ";
    } else {
        throw std::invalid_argument("nedozvoljen operator");
    }
    s << *_desni;
}

ASTCvor* BinarnaOperacija::Kloniraj() const {
    return new BinarnaOperacija(*this);
}

/***********************************************************/

UnarnaOperacija::UnarnaOperacija(const std::string& op, ASTCvor* izraz) : _op(op), _izraz(izraz) {}

UnarnaOperacija::UnarnaOperacija(const UnarnaOperacija& uo) : _op(uo._op), _izraz(uo._izraz->Kloniraj()) {}

UnarnaOperacija::~UnarnaOperacija() {
    delete _izraz;
}

int UnarnaOperacija::Interpretiraj(TablicaSimbola& ts) const {
    int i = _izraz->Interpretiraj(ts);
    
    if(_op == "-") {
        return -i;
    } else if(_op == "~") {
        return ~i;
    } else {
        throw std::invalid_argument("nedozvoljen operator");
    }
} 

void UnarnaOperacija::Ispisi(std::ostream& s) const {
    if(_op == "-") {
        s << "-";
    } else if(_op == "~") {
        s << "~";
    } else {
        throw std::invalid_argument("nedozvoljen operator");
    }
    s << *_izraz;
}

ASTCvor* UnarnaOperacija::Kloniraj() const {
    return new UnarnaOperacija(*this);
}

/*********************************************************/

Siftovanje::Siftovanje(const std::string& op, ASTCvor* izraz, int b) : _op(op), _izraz(izraz), _br(b) {}

Siftovanje::Siftovanje(const Siftovanje& s) : _op(s._op), _izraz(s._izraz->Kloniraj()), _br(s._br) {}

Siftovanje::~Siftovanje() {
    delete _izraz;
}

int Siftovanje::Interpretiraj(TablicaSimbola& ts) const {
    int i = _izraz->Interpretiraj(ts);
    if(_op == "<<") {
        return i << _br;
    } else if(_op == ">>") {
        return i >> _br;
    } else {
        throw std::invalid_argument("nedozvoljen operator");
    }
} 
void Siftovanje::Ispisi(std::ostream& s) const {
    s << *_izraz;
    if(_op == ">>") {
        s << " >> ";
    } else if(_op == "<<") {
        s << " << ";
    } else {
        throw std::invalid_argument("nedozvoljen operator");
    }
    s << _br;
}

ASTCvor* Siftovanje::Kloniraj() const {
    return new Siftovanje(*this);
}

/*******************************************************/

Grupisanje::Grupisanje(ASTCvor* izraz) : _izraz(izraz) {}

Grupisanje::Grupisanje(const Grupisanje& g) : _izraz(g._izraz->Kloniraj()) {}

Grupisanje::~Grupisanje() {
    delete _izraz;
}

int Grupisanje::Interpretiraj(TablicaSimbola& ts) const {
    return _izraz->Interpretiraj(ts);
}

void Grupisanje::Ispisi(std::ostream& s) const {
    s << "(" << *_izraz << ")";
}

ASTCvor* Grupisanje::Kloniraj() const {
    return new Grupisanje(*this);
}

/*********************************************************************/

Promenljiva::Promenljiva(std::string& id) : _id(id) {}

int Promenljiva::Interpretiraj(TablicaSimbola& ts) const {
    return ts.VrednostPromenljive(_id);
}

void Promenljiva::Ispisi(std::ostream& s) const {
    s << _id;
}

ASTCvor* Promenljiva::Kloniraj() const {
    return new Promenljiva(*this);
}

/*********************************************************************/

Konstanta::Konstanta(int vr) : _vr(vr) {}

int Konstanta::Interpretiraj(TablicaSimbola& ts) const {
    return _vr;
}

void Konstanta::Ispisi(std::ostream& s) const {
    s << _vr;
}

ASTCvor* Konstanta::Kloniraj() const {
    return new Konstanta(*this);
}