#include <stdio.h>
#include <stdlib.h>
#include "liste.h"

void izmeni(Cvor** glava, Cvor** lista) {

    if(*glava == NULL || *lista == NULL) {
        return;
    }

    int suma_prethodnika = 0;
    int suma_sledbenika = 0;

    Cvor* tmp = *glava;
    while(tmp != *lista) {
        suma_prethodnika += tmp->vrednost;
        tmp = tmp->sledeci;
    }
    tmp = (*lista)->sledeci;
    while(tmp != NULL) {
        suma_sledbenika += tmp->vrednost;
        tmp = tmp->sledeci;
    }
    
    izmeni(glava, &(*lista)->sledeci);
    
    if(suma_prethodnika > suma_sledbenika) {
        (*lista)->vrednost = 0;
    }
}

int main() {

    Cvor* lista = NULL;
    ucitaj_listu(&lista, stdin);

    izmeni(&lista, &lista);
    ispisi_listu(lista, stdout);

    oslobodi_listu(lista);
    exit(EXIT_SUCCESS);
}