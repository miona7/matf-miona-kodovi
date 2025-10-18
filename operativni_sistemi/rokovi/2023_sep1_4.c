#include <stdio.h>
#include <stdlib.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>

#define provera_greske(uslov, poruka) \
    do { \
        if(!(uslov)) { \
            fprintf(stderr, "%s\n", poruka); \
            exit(EXIT_FAILURE); \
        } \
    } while(0)

#define provera_greske_niti(gr, poruka) \
    do { \
        int greska = gr; \
        if(greska) { \
            errno = greska; \
            provera_greske(0, poruka); \
        } \
    } while(0)

typedef struct {
    int br_niti;
} ULAZNI_ARG;

typedef struct {
    int suma;
} IZLAZNI_ARG;

int n;
int* niz;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int suma = 0;

void* funkcija_niti(void* arg) {

    ULAZNI_ARG* ulaz = (ULAZNI_ARG*)arg;

    int zbir = 0;
    int x = niz[ulaz->br_niti];
    
    while(x) {
        zbir += x % 10;
        x /= 10;
    }

    provera_greske_niti(pthread_mutex_lock(&mutex), "");
    suma += zbir;
    provera_greske_niti(pthread_mutex_unlock(&mutex), "");

    IZLAZNI_ARG* rez = (IZLAZNI_ARG*)malloc(sizeof(IZLAZNI_ARG));
    provera_greske(rez != NULL, "");
    rez->suma = zbir;
    return rez;
}

int main(int argc, char** argv) {

    fscanf(stdin, "%d", &n);
    niz = (int*)malloc(n*sizeof(int));
    provera_greske(niz != NULL, "");
    for(int i = 0; i < n; i++) {
        fscanf(stdin, "%d", &niz[i]);
    }

    pthread_t* niti = (pthread_t*)malloc(n*sizeof(pthread_t));
    provera_greske(niti != NULL, "");

    ULAZNI_ARG* argumenti = (ULAZNI_ARG*)malloc(n*sizeof(ULAZNI_ARG));
    provera_greske(argumenti != NULL, "");

    for(int i = 0; i < n; i++) {
        argumenti[i].br_niti = i;
        provera_greske_niti(pthread_create(&niti[i], NULL, funkcija_niti, &argumenti[i]), "");
    }

    for(int i = 0; i < n; i++) {
        IZLAZNI_ARG* rez = NULL;
        provera_greske_niti(pthread_join(niti[i], (void**)&rez), "");
        free(rez);
    }

    fprintf(stdout, "%d\n", suma);

    free(niz);
    free(niti);
    free(argumenti);
    exit(EXIT_SUCCESS);
}