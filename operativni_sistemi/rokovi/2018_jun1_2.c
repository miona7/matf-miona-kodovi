#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include <pthread.h>
#include <errno.h>

#define provera_greske(uslov, poruka) \
    do { \
        if(!(uslov)) { \
            fprintf(stderr, "%s\n", poruka); \
            exit(EXIT_FAILURE); \
        } \
    } while(0)

#define provera_greske_niti(greska, poruka) \
    do { \
        int gr = greska; \
        if(gr) { \
            errno = gr; \
            provera_greske(0, poruka); \
        } \
    } while(0)

#define BR_NITI (26)

typedef struct {
    char* ulaz;
    char c;
} ULAZNI_ARG;

typedef struct {
    int broj;
    char c;
} IZLAZNI_ARG;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* funkcija_niti(void* arg) {

    ULAZNI_ARG* ulaz = (ULAZNI_ARG*)arg;

    FILE* f = fopen(ulaz->ulaz, "r");
    provera_greske(f != NULL, "");

    int brojac = 0;
    char c;
    while((c = fgetc(f)) != EOF) {
        if(tolower(c) == ulaz->c) {
            brojac++;
        }
    }

    IZLAZNI_ARG* izlaz = (IZLAZNI_ARG*)malloc(sizeof(IZLAZNI_ARG));
    provera_greske(izlaz != NULL, "");
    izlaz->broj = brojac;
    izlaz->c = ulaz->c;
    return izlaz;
}

int main(int argc, char** argv) {

    provera_greske(argc == 2, "");

    pthread_t* niti = (pthread_t*)malloc(BR_NITI * sizeof(pthread_t));
    provera_greske(niti != NULL, ""); 

    ULAZNI_ARG* argumenti = (ULAZNI_ARG*)malloc(BR_NITI * sizeof(ULAZNI_ARG));
    provera_greske(argumenti != NULL, "");

    for(int i = 0; i < BR_NITI; i++) {
        argumenti[i].ulaz = argv[1];
        argumenti[i].c = 'a' + i;
        provera_greske_niti(pthread_create(&niti[i], NULL, funkcija_niti, &argumenti[i]), "");
    }

    int max = -1; char max_c;
    for(int i = 0 ; i < BR_NITI; i++) {
        IZLAZNI_ARG* rez = NULL;
        provera_greske_niti(pthread_join(niti[i], (void**)&rez), "");
        fprintf(stdout, "%d ", rez->broj);
        provera_greske_niti(pthread_mutex_lock(&mutex), "");
        if(rez->broj > max) {
            max = rez->broj;
            max_c = rez->c;
        }
        provera_greske_niti(pthread_mutex_unlock(&mutex), "");
        free(rez);
    }
    fprintf(stdout, "\n");
    fprintf(stdout, "%c\n", max_c);

    free(niti);
    free(argumenti);
    exit(EXIT_SUCCESS);
}