#include <stdio.h>
#include <stdlib.h>
#include "stabla.h"

void izracunaj(Cvor* koren, int* suma) {

    if(koren == NULL) {
        return;
    }
    if(koren->levo == NULL && koren->desno == NULL) {
        return;
    }
    if(koren->levo == NULL || koren->desno == NULL) {
        *suma += koren->vrednost;
    }

    izracunaj(koren->levo, suma);
    izracunaj(koren->desno, suma);
}

void ispisi_infiksno(Cvor* koren, int suma) {

    if(koren != NULL) {
        ispisi_infiksno(koren->levo, suma);
        if(koren->vrednost > suma) {
            fprintf(stdout, "%d ", koren->vrednost);
        }
        ispisi_infiksno(koren->desno, suma);
    }
}

int main() {

    Cvor* koren = NULL;
    ucitaj_stablo(&koren, stdin);

    int suma = 0;
    izracunaj(koren, &suma);
    fprintf(stdout, "%d ", suma);

    ispisi_infiksno(koren, suma);
    fprintf(stdout, "\n");

    oslobodi(koren);
    exit(EXIT_SUCCESS);
}
