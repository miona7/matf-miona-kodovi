#include <stdio.h>
#include <stdlib.h>
#include "stabla.h"
#define MIN -1

int jeste_simetricno(Cvor* koren1, Cvor* koren2, int* suma) {

    if(koren1 == NULL && koren2 == NULL) {
        return 1;
    }
    if(koren1 == NULL || koren2 == NULL) {
        return 0;
    }

    *suma += koren1->vrednost + koren2->vrednost;
    return jeste_simetricno(koren1->levo, koren2->desno, suma) && jeste_simetricno(koren1->desno, koren2->levo, suma);
}

int main() {

    Cvor* koren = NULL;
    ucitaj_stablo(&koren, stdin);

    int suma = 0;
    if(koren != NULL) {
        suma += koren->vrednost;
        if(jeste_simetricno(koren->levo, koren->desno, &suma)) {
            fprintf(stdout, "%d\n", suma);
        }
        else {
            fprintf(stdout, "%d\n", MIN);
        }
    }
    else {
        fprintf(stdout, "%d\n", suma);
    }

    oslobodi(koren);
    exit(EXIT_SUCCESS);
}
