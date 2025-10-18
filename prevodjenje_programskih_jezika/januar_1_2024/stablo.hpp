#ifndef STABLO_HPP
#define STABLO_HPP

#include <iostream>
#include <vector>
#include <bitset>
#include "tablicaSimbola.hpp"

class ASTCvor {
    public:
        virtual ~ASTCvor();

        virtual int Interpretiraj(TablicaSimbola& ts) const = 0; 
        virtual void Ispisi(std::ostream& s) const = 0;
        virtual ASTCvor* Kloniraj() const = 0;
};

std::ostream& operator<<(std::ostream& s, const ASTCvor& c);

class NizNaredbi : public ASTCvor {
    public:
        NizNaredbi();
        NizNaredbi(const NizNaredbi& nn);
        ~NizNaredbi();

        void DodajNaredbu(ASTCvor* n);

        int Interpretiraj(TablicaSimbola& ts) const override; 
        void Ispisi(std::ostream& s) const override;
        ASTCvor* Kloniraj() const override;

    private:
        std::vector<ASTCvor*> _naredbe;
};

class Deklaracija : public ASTCvor {
    public:
        Deklaracija(const std::string& s);

        int Interpretiraj(TablicaSimbola& ts) const override; 
        void Ispisi(std::ostream& s) const override;
        ASTCvor* Kloniraj() const override;

    private:
        std::string _id;
};

class Definicija : public ASTCvor {
    public:
        Definicija(const std::string& s, ASTCvor* i);
        Definicija(const Definicija& d);
        ~Definicija();

        int Interpretiraj(TablicaSimbola& ts) const override; 
        void Ispisi(std::ostream& s) const override;
        ASTCvor* Kloniraj() const override;

    private:
        std::string _id;
        ASTCvor* _izraz;
};

class Dodela : public ASTCvor {
    public:
        Dodela(const std::string& s, ASTCvor* i);
        Dodela(const Dodela& d);
        ~Dodela();

        int Interpretiraj(TablicaSimbola& ts) const override; 
        void Ispisi(std::ostream& s) const override;
        ASTCvor* Kloniraj() const override;

    private:
        std::string _id;
        ASTCvor* _izraz;
};

class Ispis : public ASTCvor {
    public:
        Ispis(char c, ASTCvor* i);
        Ispis(ASTCvor* i);
        Ispis(const Ispis& i);
        ~Ispis();

        int Interpretiraj(TablicaSimbola& ts) const override; 
        void Ispisi(std::ostream& s) const override;
        ASTCvor* Kloniraj() const override;

    private:
        char _format;
        ASTCvor* _izraz;
        bool _logicka;
};

class BinarnaOperacija : public ASTCvor {
    public:
        BinarnaOperacija(const std::string& op, ASTCvor* levi, ASTCvor* desni);
        BinarnaOperacija(const BinarnaOperacija& bo);
        ~BinarnaOperacija();

        int Interpretiraj(TablicaSimbola& ts) const override; 
        void Ispisi(std::ostream& s) const override;
        ASTCvor* Kloniraj() const override;

    private:
        std::string _op;
        ASTCvor* _levi;
        ASTCvor* _desni;
};

class UnarnaOperacija : public ASTCvor {
    public:
        UnarnaOperacija(const std::string& op, ASTCvor* izraz);
        UnarnaOperacija(const UnarnaOperacija& uo);
        ~UnarnaOperacija();

        int Interpretiraj(TablicaSimbola& ts) const override; 
        void Ispisi(std::ostream& s) const override;
        ASTCvor* Kloniraj() const override;

    private:
        std::string _op;
        ASTCvor* _izraz;
};

class Siftovanje : public ASTCvor {
    public:
        Siftovanje(const std::string& op, ASTCvor* izraz, int b);
        Siftovanje(const Siftovanje& s);
        ~Siftovanje();

        int Interpretiraj(TablicaSimbola& ts) const override; 
        void Ispisi(std::ostream& s) const override;
        ASTCvor* Kloniraj() const override;

    private:
        std::string _op;
        ASTCvor* _izraz;
        int _br;
};

class Grupisanje : public ASTCvor {
    public:
        Grupisanje(ASTCvor* izraz);
        Grupisanje(const Grupisanje& g);
        ~Grupisanje();

        int Interpretiraj(TablicaSimbola& ts) const override; 
        void Ispisi(std::ostream& s) const override;
        ASTCvor* Kloniraj() const override;

    private:
        ASTCvor* _izraz;
};

class Promenljiva : public ASTCvor {
    public:
        Promenljiva(std::string& id);

        int Interpretiraj(TablicaSimbola& ts) const override; 
        void Ispisi(std::ostream& s) const override;
        ASTCvor* Kloniraj() const override;

    private:
        std::string _id;
};

class Konstanta : public ASTCvor {
    public:
        Konstanta(int vr);

        int Interpretiraj(TablicaSimbola& ts) const override; 
        void Ispisi(std::ostream& s) const override;
        ASTCvor* Kloniraj() const override;

    private:
        int _vr;
};

#endif