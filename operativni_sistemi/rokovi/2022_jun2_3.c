#define _XOPEN_SOURCE (700)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
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

#define MAX (30)

typedef struct {
    int br_niti;
} ULAZNI_ARG;

int* niz;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int suma = 0;

void* funkcija_niti(void* arg) {

    ULAZNI_ARG* ulaz = (ULAZNI_ARG*)arg;

    char brojevi[MAX];
    sprintf(brojevi, "%d", niz[ulaz->br_niti]);
    
    int n = strlen(brojevi);
    char tmp = brojevi[n-1];
    brojevi[n-1] = brojevi[0];
    brojevi[0] = tmp;

    int novo_x = atoi(brojevi);
    niz[ulaz->br_niti] = novo_x;

    provera_greske_niti(pthread_mutex_lock(&mutex), "");
    suma += novo_x;
    provera_greske_niti(pthread_mutex_unlock(&mutex), "");

    return NULL;
}

int main(int argc, char** argv) {

    int n;
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
        provera_greske_niti(pthread_join(niti[i], NULL), "");
    }

    for(int i = 0; i < n; i++) {
        fprintf(stdout, "%d ", niz[i]);
    }

    fprintf(stdout, "\n%d\n", suma);

    free(niz);
    free(niti);
    free(argumenti);
    exit(EXIT_SUCCESS);
} 