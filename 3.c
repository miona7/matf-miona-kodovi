#include <stdio.h>
#include <stdlib.h>
#include "stabla.h"
#define MIN 0

int broj_cvorova(Cvor* koren, int n, int k) {

    if(koren == NULL) {
        return 0;
    }

    int brojac = 0;
    if(n > k - 1) {
        brojac = 1;
    }

    return brojac + broj_cvorova(koren->levo, n + 1, k) + broj_cvorova(koren->desno, n + 1, k);
}

int main() {

    int k;
    fscanf(stdin, "%d", &k);
    if(k < MIN) {
        greska();
    }

    Cvor* koren = NULL;
    ucitaj_stablo(&koren, stdin);

    fprintf(stdout, "%d\n", broj_cvorova(koren, 0, k));

    oslobodi(koren);
    exit(EXIT_SUCCESS);
}
