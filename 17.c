#include <stdio.h>
#include <stdlib.h>
#include "liste.h"

Cvor* izmeni(Cvor* lista) {

    if(lista == NULL) {
        return NULL;
    }
    if(lista->sledeci == NULL) {
        return lista;
    }

    if(lista->sledeci->vrednost < lista->vrednost) {
        Cvor* tmp = lista->sledeci;
        lista->sledeci = tmp->sledeci;
        free(tmp);
        lista = izmeni(lista);
        return lista;
    }
    else {
        lista->sledeci = izmeni(lista->sledeci);
        return lista;
    }

}

int main() {

    Cvor* lista = NULL;
    ucitaj_listu(&lista, stdin);

    lista = izmeni(lista);
    ispisi_listu(lista, stdout);

    oslobodi_listu(lista);
    exit(EXIT_SUCCESS);
}