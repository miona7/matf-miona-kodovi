#include <stdio.h>
#include <stdlib.h>
#define MIN 1
#define MAX_V 21
#define MAX 101
#define KORAK 10

void greska() {
    fprintf(stderr, "-1\n");
    exit(EXIT_FAILURE);
}

typedef struct {

    char ime[MAX];
    char prezime[MAX];
    int godina;

} NAUCNIK;

int izracunaj_vek(NAUCNIK* a) {

    int x = a->godina;

    return x / 100 + 1;
}

int uporedi(const void* a, const void* b) {

    int x = *((int*)a);
    NAUCNIK* y = (NAUCNIK*)b;
    int z = izracunaj_vek(y);

    if(x == z) {
        return 0;
    }
    else if(x > z) {
        return 1;
    }
    else {
        return -1;
    }
}

int main(int argc, char** argv) {

    if(argc != 3) {
        greska();
    }

    int v = atoi(argv[2]);
    if(v < MIN || v > MAX_V) {
        greska();
    }

    FILE* ulaz = fopen(argv[1], "r");
    if(ulaz == NULL) {
        greska();
    }

    NAUCNIK* niz_naucnika = (NAUCNIK*)malloc(sizeof(NAUCNIK));
    if(niz_naucnika == NULL) {
        greska();
    }
    int alocirano = 1; int i = 0;

    while(fscanf(ulaz, "%s%s%d", niz_naucnika[i].ime, niz_naucnika[i].prezime, &niz_naucnika[i].godina) != EOF) {
        if(i + 1 == alocirano) {
            alocirano += KORAK;
            niz_naucnika = (NAUCNIK*)realloc(niz_naucnika, alocirano*sizeof(NAUCNIK));
            if(niz_naucnika == NULL) {
                greska();
            }
        }
        i++;
    }
    int n = i;
    NAUCNIK* trazeni = (NAUCNIK*)bsearch(&v, niz_naucnika, n, sizeof(NAUCNIK), uporedi);
    
    if(trazeni != NULL) {
        while(izracunaj_vek(trazeni) == v) {
            trazeni--;
        }
        trazeni++;
        while(izracunaj_vek(trazeni) == v) {
            fprintf(stdout, "%s %s\n", trazeni->ime, trazeni->prezime);
            trazeni++;
        }
    }
    else {
        fprintf(stdout, "\n");
    }

    free(niz_naucnika);
    fclose(ulaz);
    exit(EXIT_SUCCESS);
}