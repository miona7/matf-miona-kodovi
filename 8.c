#include <stdio.h>
#include <stdlib.h>
#include "liste.h"
#define MIN 0

Cvor* dodaj_cvorove(Cvor* lista, int k, int p) {

    if(lista == NULL) {
        return NULL;
    }
    if(lista->sledeci == NULL) {
        return lista;
    }
    int suma = lista->vrednost + lista->sledeci->vrednost;
    if(suma % k == p || ((suma < MIN && suma + k == p))) {
        Cvor* tmp1 = napravi_cvor(MIN);
        Cvor* tmp2 = napravi_cvor(MIN);
        tmp1->sledeci = tmp2;
        tmp2->sledeci = lista->sledeci;
        lista->sledeci = tmp1;
        tmp2->sledeci = dodaj_cvorove(tmp2->sledeci, k, p);
        return lista;
    }
    else {
        lista->sledeci = dodaj_cvorove(lista->sledeci, k, p);
        return lista;
    }
}

int main() {

    int k, p;
    fscanf(stdin, "%d%d", &k, &p);
    if(p >= k) {
        greska();
    }

    Cvor* lista = NULL;
    ucitaj_listu(&lista, stdin);

    lista = dodaj_cvorove(lista, k, p);

    ispisi_listu(lista, stdout);
    oslobodi_listu(lista);
    exit(EXIT_SUCCESS);
}