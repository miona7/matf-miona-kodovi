#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MIN 1
#define MAX 21 

void greska() {
    fprintf(stderr, "-1\n");
    exit(EXIT_FAILURE);
}

typedef struct {
    
    char ime[MAX];
    char boja[MAX];
    int povrsina;

} FIGURA;

int uporedi(const void* a, const void* b) {

    FIGURA* x = (FIGURA*)a;
    FIGURA* y = (FIGURA*)b;

    if(strcmp(x->ime, y->ime) < 0) {
        return 1;
    }
    else if(strcmp(x->ime, y->ime) == 0) {
        if(strcmp(x->boja, y->boja) < 0) {
            return -1;
        }
        else if(strcmp(x->boja, y->boja) == 0) {
            if(x->povrsina < y->povrsina) {
                return 1;
            }
            else if(x->povrsina == y->povrsina) {
                return 0;
            }
            else {
                return -1;
            }
        }
        else {
            return 1;
        }
    }
    else {
        return -1;
    }
}

int main(int argc, char** argv) {

    if(argc != 2) {
        greska();
    }

    FILE* ulaz = fopen(argv[1], "r");
    if(ulaz == NULL) {
        greska();
    }

    int n;
    fscanf(ulaz, "%d", &n);
    if(n < MIN) {
        greska();
    }

    FIGURA* niz_figura = (FIGURA*)malloc(n * sizeof(FIGURA));
    if(niz_figura == NULL) {
        greska();
    }

    int i;
    for(i = 0; i < n; i++) {
        fscanf(ulaz, "%s%s%d", niz_figura[i].ime, niz_figura[i].boja, &niz_figura[i].povrsina);
    }

    qsort(niz_figura, n, sizeof(FIGURA), uporedi);

    for(i = 0; i < n; i++) {
        fprintf(stdout, "%s %s %d\n", niz_figura[i].ime, niz_figura[i].boja, niz_figura[i].povrsina);
    }

    free(niz_figura);
    fclose(ulaz);
    exit(EXIT_SUCCESS);
}