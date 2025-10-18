#ifndef TABLICA_HPP
#define TABLICA_HPP

#include <iostream>
#include <string>
#include <map>
#include <exception>

class TablicaSimbola {
    public:
        TablicaSimbola(); 

        void DefinisiPromenljivu(const std::string& s, int vr);
        void DodeliVrednost(const std::string& s, int vr);
        int VrednostPromenljive(const std::string& s) const;

    private:
        std::map<std::string, int> _promenljive;
};

#endif