#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MIN 1
#define MAX 22

void greska() {
    fprintf(stderr, "-1\n");
    exit(EXIT_FAILURE);
}

typedef struct _cvor {
    
    char ime_cokolade[MAX];
    int kolicina;
    struct _cvor* sledeci;

} Cvor;

Cvor* napraviCvor(char* ime, int grami) {

    Cvor* novi = (Cvor*)malloc(sizeof(Cvor));
    if(novi == NULL) {
        greska();
    }
    strcpy(novi->ime_cokolade, ime);
    novi->kolicina = grami;
    novi->sledeci = NULL;

    return novi;
}

void dodajNaKraj(Cvor** glava, char* ime, int grami) {

    if(*glava == NULL) {
        Cvor* novi = napraviCvor(ime, grami);
        *glava = novi;
        return;
    }
    dodajNaKraj(&(*glava)->sledeci, ime, grami);
}

Cvor* izbrisi(Cvor* glava, char* ime, int grami) {

    if(glava == NULL) {
        return NULL;
    }
    if(strcmp(glava->ime_cokolade, ime) == 0 || glava->kolicina < grami) {
        Cvor* tmp = glava->sledeci;
        free(glava);
        tmp = izbrisi(tmp, ime, grami);
        return tmp;
    }
    else {
        glava->sledeci = izbrisi(glava->sledeci, ime, grami);
        return glava;
    }
}

void ispisi(Cvor* glava) {
    
    if(glava == NULL) {
        fprintf(stdout, "\n");
        return;
    }
    while(glava != NULL) {
        fprintf(stdout, "%s %d\n", glava->ime_cokolade, glava->kolicina);
        glava = glava->sledeci;
    }
}

void oslobodi(Cvor* glava) {

    if(glava != NULL) {
        oslobodi(glava->sledeci);
        free(glava);
    }
}

int main(int argc, char** argv) {

    if(argc != 3) {
        greska();
    }

    char trazena_cokolada[MAX]; 
    strcpy(trazena_cokolada, argv[1]);

    int trazena_kolicina = atoi(argv[2]);
    if(trazena_kolicina < MIN) {
        greska();
    }

    char ime[MAX];
    int kolicina;

    Cvor* lista = NULL;
    while(fscanf(stdin, "%s%d", ime, &kolicina) != EOF) {
        dodajNaKraj(&lista, ime, kolicina);
    }

    fprintf(stdout, "nova lista:\n");

    Cvor* lista1 = izbrisi(lista, trazena_cokolada, trazena_kolicina);
    ispisi(lista1);

    oslobodi(lista1);
    exit(EXIT_SUCCESS);
}