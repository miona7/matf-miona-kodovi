#ifndef TABELA_HPP
#define TABELA_HPP

#include <iostream>
#include <string>
#include <map>
#include <exception>

class TabelaSimbola {
    public:
        TabelaSimbola();

        void Ispisi(std::ostream& s) const;
        void DefinisiPromenljivu(const std::string& id, const std::string& v);
        void DodeliVrednost(const std::string& id, const std::string& v);
        std::string VrednostPromelnjive(const std::string& id) const;

    private:
        std::map<std::string, std::string> _promenljive;
};

std::ostream& operator<<(std::ostream& s, const TabelaSimbola& ts);

#endif