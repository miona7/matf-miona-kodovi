#ifndef VEHICLES_HPP
#define VEHICLES_HPP

#include <iostream>
#include <string>

// apstraktna klasa == klasa koja sadrzi samo virtualne metode 
class Vehicle {
    public:
        // virtual ~Vehicle() = default;
        // zbog linkovanja u virtualnoj tabeli kod abstraktnih klasa mora da postoji definicija u cpp fajlu iako je = default
        virtual ~Vehicle();

        // cisto virtualni metodi
        virtual std::string type() const = 0;
        virtual Vehicle* copy() const = 0;

        // zelimo da se drugaciji tipovi vozila drugacije ispisuju, ali kako operator << nije deo nase klase on ne moze biti virtualan, pa ce ovo biti prijateljski metod koji ce pozivati nas protected virtualni metod za ispis koji ce imati polimorfno ponasanje
        friend std::ostream& operator<<(std::ostream&, const Vehicle&);

    protected:
        // samo nase podklase mogu pozivati konstruktor, tj nije moguce instancirati objekat tipa Vehicle
        Vehicle(unsigned, unsigned);

        // nije cisto virtualni metod jer cemo imati podrazumevani ispis
        virtual void print(std::ostream&) const;


    private:
        unsigned m_wheels;
        unsigned m_seats;
};

#endif // VEHICLES_HPP