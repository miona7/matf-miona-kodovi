#ifndef FRACTION_HPP
#define FRACTION_HPP

#include <iostream>

namespace matf {
    class Fraction {
        public:
            Fraction(int numerator = 0, unsigned denominator = 1);

            int Numerator() const;
            unsigned Denominator() const;
            
            Fraction operator-() const;

            Fraction operator+(const Fraction&) const;
            Fraction operator-(const Fraction&) const;

            // prefiksni, nemamo const jer ovi operatori menjaju nas objekat
            Fraction operator++();
            // postfiksni, da bi se razlikovali potpisi imamo "lazni parametar"
            Fraction operator++(int);

            bool operator==(const Fraction&) const;
            bool operator!=(const Fraction&) const;

            // operator konverzije, povratna vrednost == naziv
            operator double() const;

            // prijateljska funkcija, dopustamo joj da pristupa nasim privatnim promenljivama
            friend std::istream& operator>>(std::istream&, Fraction&);

        private:
            int m_numerator;
            unsigned m_denominator;

            void Reduce();
    };

std::ostream& operator<<(std::ostream&, const Fraction&);
std::istream& operator>>(std::istream&, Fraction&);

}

#endif // FRACTION_HPP