#include "stablo.hpp"

ASTCvor::~ASTCvor() {}

std::ostream& operator<<(std::ostream& s, const ASTCvor& c) {
    c.Ispisi(s);
    return s;
}

/*********************************************************/

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

void NizNaredbi::Ispisi(std::ostream& s) const {
    for(size_t i = 0; i < _naredbe.size(); i++) {
        s << *_naredbe[i] << ";" << std::endl;
    }
}

std::string NizNaredbi::Interpretiraj(TabelaSimbola& ts) const {
    for(size_t i = 0; i < _naredbe.size(); i++) {
        _naredbe[i]->Interpretiraj(ts);
    }
    return "";
}

ASTCvor* NizNaredbi::Kloniraj() const {
    return new NizNaredbi(*this);
}

/*****************************************************************/

Deklaracija::Deklaracija(const std::string& s) : _id(s) {}

void Deklaracija::Ispisi(std::ostream& s) const {
    s << "string " << _id;
}

std::string Deklaracija::Interpretiraj(TabelaSimbola& ts) const {
    ts.DefinisiPromenljivu(_id, "");
    return "";
}

ASTCvor* Deklaracija::Kloniraj() const {
    return new Deklaracija(*this);
}

/*****************************************************************/

Definicija::Definicija(const std::string& s, ASTCvor* izraz) : _id(s), _izraz(izraz) {}

Definicija::Definicija(const Definicija& d) : _id(d._id), _izraz(d._izraz->Kloniraj()) {}

Definicija::~Definicija() {
    delete _izraz;
}

void Definicija::Ispisi(std::ostream& s) const {
    s << "string " << _id << " = " << *_izraz;
}

std::string Definicija::Interpretiraj(TabelaSimbola& ts) const {
    ts.DefinisiPromenljivu(_id, _izraz->Interpretiraj(ts));
    return "";
}

ASTCvor* Definicija::Kloniraj() const {
    return new Definicija(*this);
}

/*****************************************************************/

Dodela::Dodela(const std::string& s, ASTCvor* izraz) : _id(s), _izraz(izraz) {}

Dodela::Dodela(const Dodela& d) : _id(d._id), _izraz(d._izraz->Kloniraj()) {}

Dodela::~Dodela() {
    delete _izraz;
}

void Dodela::Ispisi(std::ostream& s) const {
    s << _id << " = " << *_izraz;
}

std::string Dodela::Interpretiraj(TabelaSimbola& ts) const {
    ts.DodeliVrednost(_id, _izraz->Interpretiraj(ts));
    return "";
}

ASTCvor* Dodela::Kloniraj() const {
    return new Dodela(*this);
}

/***********************************************************************/

Ispis::Ispis(std::string izlaz, ASTCvor* izraz) : _izlaz(izlaz), _izraz(izraz) {}

Ispis::Ispis(const Ispis& i) : _izlaz(i._izlaz), _izraz(i._izraz->Kloniraj()) {}

Ispis::~Ispis() {
    delete _izraz;
}

void Ispis::Ispisi(std::ostream& s) const {
    if(_izlaz == "cout") {
        s << "std_output << " << *_izraz;
    } else if(_izlaz == "cerr") {
        s << "std_error << " << *_izraz;
    } else {
        throw std::invalid_argument("nepoznat izlaz");
    }
}

std::string Ispis::Interpretiraj(TabelaSimbola& ts) const {
    if(_izlaz == "cout") {
        std::cout << _izraz->Interpretiraj(ts) << std::endl;
    } else if(_izlaz == "cerr") {
        std::cerr << _izraz->Interpretiraj(ts) << std::endl;
    } else {
        throw std::invalid_argument("nepoznat izlaz");
    }
    return "";
}

ASTCvor* Ispis::Kloniraj() const {
    return new Ispis(*this);
}

/***********************************************************************/

Unos::Unos(std::string s) : _id(s) {}

void Unos::Ispisi(std::ostream& s) const {
    s << "std_input >> " << _id;
}

std::string Unos::Interpretiraj(TabelaSimbola& ts) const {
    std::string s;
    std::cin >> s;
    ts.DodeliVrednost(_id, s);
    return s;
}

ASTCvor* Unos::Kloniraj() const {
    return new Unos(*this);
}

/********************************************************************************/

IspisSvih::IspisSvih() {}

void IspisSvih::Ispisi(std::ostream& s) const {
    s << "print_ALL";
}

std::string IspisSvih::Interpretiraj(TabelaSimbola& ts) const {
    std::cout << ts << std::endl;
    return "";
}

ASTCvor* IspisSvih::Kloniraj() const {
    return new IspisSvih(*this);
}

/******************************************************************************/

IfNoElse::IfNoElse(ASTCvor* uslov, ASTCvor* naredba) : _uslov(uslov), _naredba(naredba) {}

IfNoElse::IfNoElse(const IfNoElse& i) : _uslov(i._uslov->Kloniraj()), _naredba(i._naredba->Kloniraj()) {}

IfNoElse::~IfNoElse() {
    delete _uslov;
    delete _naredba;
}

void IfNoElse::Ispisi(std::ostream& s) const {
    s << "if(" << *_uslov << ") {" << std::endl << '\t' << *_naredba << std::endl << "}";
}

std::string IfNoElse::Interpretiraj(TabelaSimbola& ts) const {
    if(_uslov->Interpretiraj(ts) == "1") {
        return _naredba->Interpretiraj(ts);
    }
    return "0";
}

ASTCvor* IfNoElse::Kloniraj() const {
    return new IfNoElse(*this);
}


/******************************************************************************/

IfElse::IfElse(ASTCvor* uslov, ASTCvor* naredba1, ASTCvor* naredba2) : _uslov(uslov), _naredba1(naredba1), _naredba2(naredba2) {}

IfElse::IfElse(const IfElse& i) : _uslov(i._uslov->Kloniraj()), _naredba1(i._naredba1->Kloniraj()), _naredba2(i._naredba2->Kloniraj()) {}

IfElse::~IfElse() {
    delete _uslov;
    delete _naredba1;
    delete _naredba2;
}

void IfElse::Ispisi(std::ostream& s) const {
    s << "if(" << *_uslov << ") {" << std::endl << '\t' << *_naredba1 << std::endl
        << "} else {" << std::endl << '\t' << *_naredba2 << std::endl << "}" ;
}

std::string IfElse::Interpretiraj(TabelaSimbola& ts) const {
    if(_uslov->Interpretiraj(ts) == "1") {
        return _naredba1->Interpretiraj(ts);
    } else {
        return _naredba2->Interpretiraj(ts);
    }
    return "";
}

ASTCvor* IfElse::Kloniraj() const {
    return new IfElse(*this);
}

/*****************************************************/

BinarnaOperacija::BinarnaOperacija(const std::string& op, ASTCvor* levi, ASTCvor* desni) : _op(op), _levi(levi), _desni(desni) {}

BinarnaOperacija::BinarnaOperacija(const BinarnaOperacija& bo) : _op(bo._op), _levi(bo._levi->Kloniraj()), _desni(bo._desni->Kloniraj()) {}

BinarnaOperacija::~BinarnaOperacija() {
    delete _levi;
    delete _desni;
}

void BinarnaOperacija::Ispisi(std::ostream& s) const {
    if(_op == "+") {
        s << *_levi << " + " << *_desni;
    } else if(_op == "*") {
        s << *_levi << " * " << *_desni;
    } else if(_op == "==") {
        s << *_levi << " == " << *_desni;
    } else if(_op == "!=") {
        s << *_levi << " != " << *_desni;
    } else {
        throw std::invalid_argument("nepoznat operator");
    }
}

std::string BinarnaOperacija::Interpretiraj(TabelaSimbola& ts) const {
    if(_op == "+") {
        return _levi->Interpretiraj(ts) + _desni->Interpretiraj(ts);
    } else if(_op == "*") {
        auto l = _levi->Interpretiraj(ts);
        auto d = _desni->Interpretiraj(ts);
        
        std::string rez = "";
        for(size_t i = 0; i < l.size() - 1 && i < l.size() - 1 && l[i] == d[i]; i++) {
            rez += l[i];
        }
        return rez;
    } else if(_op == "==") {
        if(_levi->Interpretiraj(ts) == _desni->Interpretiraj(ts)) {
            return "1";
        } else {
            return "0";
        }
    } else if(_op == "!=") {
        if(_levi->Interpretiraj(ts) != _desni->Interpretiraj(ts)) {
            return "1";
        } else {
            return "0";
        }
    } else {
        throw std::invalid_argument("nepoznat operator");
    }
}

ASTCvor* BinarnaOperacija::Kloniraj() const {
    return new BinarnaOperacija(*this);
}

/**********************************************************************/


UnarnaOperacija::UnarnaOperacija(ASTCvor* izraz) : _izraz(izraz) {}

UnarnaOperacija::UnarnaOperacija(const UnarnaOperacija& uo) : _izraz(uo._izraz->Kloniraj()) {}

UnarnaOperacija::~UnarnaOperacija() {
    delete _izraz;
}

void UnarnaOperacija::Ispisi(std::ostream& s) const {
    s << "~" << *_izraz;
}

std::string UnarnaOperacija::Interpretiraj(TabelaSimbola& ts) const {
   auto i = _izraz->Interpretiraj(ts);
   std::reverse(i.begin(), i.end());
   return i;
}

ASTCvor* UnarnaOperacija::Kloniraj() const {
    return new UnarnaOperacija(*this);
}

/************************************************************************/

Grupisanje::Grupisanje(ASTCvor* izraz) : _izraz(izraz) {}

Grupisanje::Grupisanje(const Grupisanje& g) : _izraz(g._izraz->Kloniraj()) {}

Grupisanje::~Grupisanje() {
    delete _izraz;
}

void Grupisanje::Ispisi(std::ostream& s) const {
    s << "(" << *_izraz << ")";
}
std::string Grupisanje::Interpretiraj(TabelaSimbola& ts) const {
    return _izraz->Interpretiraj(ts);
}

ASTCvor* Grupisanje::Kloniraj() const {
    return new Grupisanje(*this);
}

/************************************************************************/

Promenljiva::Promenljiva(const std::string& s) : _id(s) {}

void Promenljiva::Ispisi(std::ostream& s) const {
    s << _id;
}

std::string Promenljiva::Interpretiraj(TabelaSimbola& ts) const {
    return ts.VrednostPromelnjive(_id);
}

ASTCvor* Promenljiva::Kloniraj() const {
    return new Promenljiva(*this);
}

/*************************************************************/

String::String(const std::string& s) : _s(s) {}

void String::Ispisi(std::ostream& s) const {
    s << _s;
}

std::string String::Interpretiraj(TabelaSimbola& ts) const {
    return _s.substr(1, _s.size() - 2);
}

ASTCvor* String::Kloniraj() const {
    return new String(*this);
}