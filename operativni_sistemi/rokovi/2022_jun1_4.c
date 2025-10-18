#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>

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

int** matrica;
int n, m;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int globalni_max = INT_MIN;

void* funkcija_niti(void* arg) {

    ULAZNI_ARG* ulaz = (ULAZNI_ARG*)arg;

    int lokalni_max = INT_MIN;
    for(int i = 0; i < m; i++) {
        if(matrica[ulaz->br_niti][i] > lokalni_max) {
            lokalni_max = matrica[ulaz->br_niti][i];
        }
    }

    provera_greske_niti(pthread_mutex_lock(&mutex), "");
    if(lokalni_max > globalni_max) {
        globalni_max = lokalni_max;
    }
    provera_greske_niti(pthread_mutex_unlock(&mutex), "");

    return NULL;
}

int main(int argc, char** argv) {

    provera_greske(argc == 2, "");

    FILE* ulaz = fopen(argv[1], "r");
    provera_greske(ulaz != NULL, "");

    fscanf(ulaz, "%d", &n);

    matrica = (int**)malloc(n*sizeof(int*));
    provera_greske(matrica != NULL, "");

    for(int i = 0; i < n; i++) {
        fscanf(ulaz, "%d", &m);
        matrica[i] = (int*)malloc(m*sizeof(int));
        provera_greske(matrica[i] != NULL, "");

        for(int j = 0; j < m; j++) {
            fscanf(ulaz, "%d", &matrica[i][j]);
        }
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

    fprintf(stdout, "%d\n", globalni_max);

    fclose(ulaz);
    for(int i = 0; i < n; i++) {
        free(matrica[i]);
    }
    free(matrica);
    free(niti);
    free(argumenti);
    exit(EXIT_SUCCESS);
}