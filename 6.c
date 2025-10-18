#include <stdio.h>
#include <stdlib.h>
#include "stabla.h"

void izracunaj(Cvor* koren, int* n) {

    if(koren == NULL) {
        return;
    }
    if(koren->levo == NULL && koren->desno == NULL) {
        if(koren->vrednost % 2 != 0) {
            *n += 1;
        }
    }

    izracunaj(koren->levo, n);
    izracunaj(koren->desno, n);
}

int main() {

    Cvor* koren = NULL;
    ucitaj_stablo(&koren, stdin);

    int n = 0;
    izracunaj(koren, &n);

    fprintf(stdout, "%d\n", n);

    oslobodi(koren);
    exit(EXIT_SUCCESS);
}
