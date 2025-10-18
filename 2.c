#include <stdio.h>
#include <stdlib.h>
#include "stabla.h"

void ispisi_cvorove(Cvor* koren, int indikator) {

    if(koren != NULL) {
        ispisi_cvorove(koren->levo, 1);
        ispisi_cvorove(koren->desno, 1);
        int brojac = indikator;
        if(koren->levo != NULL) {
            brojac++;
        }
        if(koren->desno != NULL) {
            brojac++;
        }
        if(brojac % 2 == 0) {
            fprintf(stdout, "%d ", koren->vrednost);
        }
    }
}

int main() {

    Cvor* koren = NULL;
    ucitaj_stablo(&koren, stdin);

    int indikator = 0;
    ispisi_cvorove(koren, indikator);
    fprintf(stdout, "\n");

    oslobodi(koren);
    exit(EXIT_SUCCESS);
}
