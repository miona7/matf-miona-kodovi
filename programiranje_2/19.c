#include <stdio.h>
#include <stdlib.h>
#define MIN 1
#define MAX 51

void greska() {
    fprintf(stderr, "-1\n");
    exit(EXIT_FAILURE);
}

typedef struct {
    
    char naziv[MAX];
    unsigned long int postanski_broj;

} GRAD;

int binarna_pretraga(GRAD* a, int l, int d, unsigned long int x) {

    while(l <= d) {
        int s = l + (d - l) / 2;

        if(a[s].postanski_broj == x) {
            return s;
        }
        else if(a[s].postanski_broj < x) {
            l = s + 1;
        }
        else {
            d = s - 1;
        } 
    }
    return -1;
}


int main(int argc, char** argv) {

    if(argc != 3) {
        greska();
    }
    FILE* ulaz = fopen(argv[1], "r");
    if(ulaz == NULL) {
        greska();
    }
    int broj_linija = atoi(argv[2]);
    if(broj_linija < MIN) {
        greska();
    }

    GRAD* niz_gradova = (GRAD*)malloc(broj_linija * sizeof(GRAD));
    if(niz_gradova == NULL) {
        greska();
    }
    
    int i;
    for(i = 0; i < broj_linija; i++) {
        fscanf(ulaz, "%s%ld", niz_gradova[i].naziv, &niz_gradova[i].postanski_broj);
    }   

    unsigned long int x;
    fscanf(stdin, "%ld", &x);

    int m = binarna_pretraga(niz_gradova, 0, broj_linija - 1, x);

    if(m != -1) {
        fprintf(stdout, "%s\n", niz_gradova[m].naziv);
    }
    else {
        fprintf(stdout, "\n");
    }

    free(niz_gradova);
    fclose(ulaz);
    exit(EXIT_SUCCESS);
}