#ifndef STABLO_HPP
#define STABLO_HPP

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "tabela.hpp"

class ASTCvor {
    public:
        virtual ~ASTCvor();

        virtual void Ispisi(std::ostream& s) const = 0;
        virtual std::string Interpretiraj(TabelaSimbola& ts) const = 0;
        virtual ASTCvor* Kloniraj() const = 0;

};

std::ostream& operator<<(std::ostream& s, const ASTCvor& c);

class NizNaredbi : public ASTCvor {
    public:
        NizNaredbi();
        NizNaredbi(const NizNaredbi& nn);
        ~NizNaredbi();

        void DodajNaredbu(ASTCvor* n);
        void Ispisi(std::ostream& s) const override;
        std::string Interpretiraj(TabelaSimbola& ts) const override;
        ASTCvor* Kloniraj() const override;

    private:
        std::vector<ASTCvor*> _naredbe;
};

class Deklaracija : public ASTCvor {
    public:
        Deklaracija(const std::string& s);

        void Ispisi(std::ostream& s) const override;
        std::string Interpretiraj(TabelaSimbola& ts) const override;
        ASTCvor* Kloniraj() const override;
    
    private:
        std::string _id;
};

class Definicija : public ASTCvor {
    public:
        Definicija(const std::string& s, ASTCvor* izraz);
        Definicija(const Definicija& d);
        ~Definicija();

        void Ispisi(std::ostream& s) const override;
        std::string Interpretiraj(TabelaSimbola& ts) const override;
        ASTCvor* Kloniraj() const override;
    
    private:
        std::string _id;
        ASTCvor* _izraz;
};

class Dodela : public ASTCvor {
    public:
        Dodela(const std::string& s, ASTCvor* izraz);
        Dodela(const Dodela& d);
        ~Dodela();

        void Ispisi(std::ostream& s) const override;
        std::string Interpretiraj(TabelaSimbola& ts) const override;
        ASTCvor* Kloniraj() const override;
    
    private:
        std::string _id;
        ASTCvor* _izraz;

};

class Ispis : public ASTCvor {
    public:
        Ispis(std::string izlaz, ASTCvor* izraz);
        Ispis(const Ispis& i);
        ~Ispis();

        void Ispisi(std::ostream& s) const override;
        std::string Interpretiraj(TabelaSimbola& ts) const override;
        ASTCvor* Kloniraj() const override;

    private:
        std::string _izlaz;
        ASTCvor* _izraz;
        bool _logicka;
};

class Unos : public ASTCvor {
    public:
        Unos(std::string s);

        void Ispisi(std::ostream& s) const override;
        std::string Interpretiraj(TabelaSimbola& ts) const override;
        ASTCvor* Kloniraj() const override;

    private:
        std::string _id;
};

class IspisSvih : public ASTCvor {
    public:
        IspisSvih();

        void Ispisi(std::ostream& s) const override;
        std::string Interpretiraj(TabelaSimbola& ts) const override;
        ASTCvor* Kloniraj() const override;
};

class IfNoElse : public ASTCvor {
    public:
        IfNoElse(ASTCvor* uslov, ASTCvor* naredba);
        IfNoElse(const IfNoElse& i);
        ~IfNoElse();

        void Ispisi(std::ostream& s) const override;
        std::string Interpretiraj(TabelaSimbola& ts) const override;
        ASTCvor* Kloniraj() const override;

    private:
        ASTCvor* _uslov;
        ASTCvor* _naredba;
};

class IfElse : public ASTCvor {
    public:
        IfElse(ASTCvor* uslov, ASTCvor* naredba1, ASTCvor* naredba2);
        IfElse(const IfElse& i);
        ~IfElse();

        void Ispisi(std::ostream& s) const override;
        std::string Interpretiraj(TabelaSimbola& ts) const override;
        ASTCvor* Kloniraj() const override;

    private:
        ASTCvor* _uslov;
        ASTCvor* _naredba1;
        ASTCvor* _naredba2;
};

class BinarnaOperacija : public ASTCvor {
    public:
        BinarnaOperacija(const std::string& op, ASTCvor* levi, ASTCvor* desni);
        BinarnaOperacija(const BinarnaOperacija& bo);
        ~BinarnaOperacija();

        void Ispisi(std::ostream& s) const override;
        std::string Interpretiraj(TabelaSimbola& ts) const override;
        ASTCvor* Kloniraj() const override;

    private:
        std::string _op;
        ASTCvor* _levi;
        ASTCvor* _desni;
};

class UnarnaOperacija : public ASTCvor {
    public:
        UnarnaOperacija(ASTCvor* izraz);
        UnarnaOperacija(const UnarnaOperacija& uo);
        ~UnarnaOperacija();

        void Ispisi(std::ostream& s) const override;
        std::string Interpretiraj(TabelaSimbola& ts) const override;
        ASTCvor* Kloniraj() const override;

    private:
        ASTCvor* _izraz;
};

class Grupisanje : public ASTCvor {
    public:
        Grupisanje(ASTCvor* izraz);
        Grupisanje(const Grupisanje& g);
        ~Grupisanje();

        void Ispisi(std::ostream& s) const override;
        std::string Interpretiraj(TabelaSimbola& ts) const override;
        ASTCvor* Kloniraj() const override;

    private:
        ASTCvor* _izraz;
};

class Promenljiva : public ASTCvor {
    public:
        Promenljiva(const std::string& s);

        void Ispisi(std::ostream& s) const override;
        std::string Interpretiraj(TabelaSimbola& ts) const override;
        ASTCvor* Kloniraj() const override;

    private:
        std::string _id;
};

class String : public ASTCvor {
    public:
        String(const std::string& s);

        void Ispisi(std::ostream& s) const override;
        std::string Interpretiraj(TabelaSimbola& ts) const override;
        ASTCvor* Kloniraj() const override;

    private:
        std::string _s;
};

#endif