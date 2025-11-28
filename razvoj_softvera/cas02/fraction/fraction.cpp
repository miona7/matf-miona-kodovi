#include "fraction.hpp"
#include <numeric>

namespace matf {
    // uz pomoc liste inicijalizacije izbegavamo dvostruku inicijalizaciju parametara (pozivao bi se najpre podrazumevani konstruktor, a zatim bi se prepisala vrednost)
    Fraction::Fraction(int numerator, unsigned denominator) : m_numerator(numerator), m_denominator(denominator) {
        Reduce();
    }

    int Fraction::Numerator() const {
        return m_numerator;
    }

    unsigned Fraction::Denominator() const {
        return m_denominator;
    }
    
    Fraction Fraction::operator-() const {
        return Fraction(-m_numerator, m_denominator);
    }

    Fraction Fraction::operator+(const Fraction& f) const {
        int res_numerator = m_numerator * f.Denominator() + m_denominator * f.Numerator();
        unsigned res_denominator = m_denominator * f.Denominator();
        return Fraction(res_numerator, res_denominator);
    }

    Fraction Fraction::operator-(const Fraction& f) const {
        return *this + (-f);
    }

    Fraction Fraction::operator++() {
        m_numerator += m_denominator;
        return *this;
    }

    Fraction Fraction::operator++(int) {
        Fraction tmp(m_numerator, m_denominator);
        ++(*this);
        return tmp;
    }

    bool Fraction::operator==(const Fraction& f) const {
        return m_numerator == f.Numerator() && m_denominator == f.Denominator();
    }

    bool Fraction::operator!=(const Fraction& f) const {
        return !(*this == f);
    }

    Fraction::operator double() const {
        return m_numerator / static_cast<double>(m_denominator);
    }

    void Fraction::Reduce() {
        const auto gcd = std::gcd(m_numerator, m_denominator);
        m_numerator /= gcd;
        m_denominator /= gcd;
    }

    std::ostream& operator<<(std::ostream& s, const Fraction& f) {
        return s << f.Numerator() << "/" << f.Denominator();
    }

    std::istream& operator>>(std::istream& s, Fraction& f) {
        char c;
        s >> f.m_numerator >> c >> f.m_denominator;
        f.Reduce();
        return s;
    }
}