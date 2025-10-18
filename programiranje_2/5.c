#include <stdio.h>
#include <stdlib.h>
#include "stabla.h"
#define MIN 0

void izracunaj(Cvor* koren, int n, int* suma_parnih, int* suma_neparnih) {

    if(koren == NULL) {
        return;
    }

    if(n % 2 == 0) {
        *suma_parnih += koren->vrednost;
    }
    else {
        *suma_neparnih += koren->vrednost;
    }
    izracunaj(koren->levo, n + 1, suma_parnih, suma_neparnih);
    izracunaj(koren->desno, n + 1, suma_parnih, suma_neparnih);
}

int main() {

    Cvor* koren = NULL;
    ucitaj_stablo(&koren, stdin);

    int suma_parnih = 0;
    int suma_neparnih = 0;

    izracunaj(koren, MIN, &suma_parnih, &suma_neparnih);
    fprintf(stdout, "%d\n", suma_parnih - suma_neparnih);

    oslobodi(koren);
    exit(EXIT_SUCCESS);
}
