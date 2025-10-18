#include <stdio.h>
#include <stdlib.h>
#include "stabla.h"
#define MIN 0

void foo(Cvor* koren, Cvor** trazeni, int* rezultat) {

    if(koren == NULL) {
        return;
    }
    if(koren->levo == NULL && koren->desno == NULL) {
        return;
    }

    if(koren->levo != NULL) {
        int razlika = abs(koren->vrednost - koren->levo->vrednost);
        if(razlika > (*rezultat)) {
            *rezultat = razlika;
            *trazeni = koren;
        }
    }
    if(koren->desno != NULL) {
        int razlika = abs(koren->vrednost - koren->desno->vrednost);
        if(razlika > (*rezultat)) {
            *rezultat = razlika;
            *trazeni = koren;
        }

    }
    foo(koren->desno, trazeni, rezultat);
    foo(koren->levo, trazeni, rezultat);
}

int main() {

    Cvor* koren = NULL;
    ucitaj_stablo(&koren, stdin);

    int razlika = 0;
    Cvor* s = NULL;
    foo(koren, &s, &razlika);

    if(s != NULL) {
        fprintf(stdout, "%d\n", s->vrednost);
    }
    else {
        fprintf(stdout, "%d\n", MIN);
    }

    oslobodi(koren);
    exit(EXIT_SUCCESS);
}
