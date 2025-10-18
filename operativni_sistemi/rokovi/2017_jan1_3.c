#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include <sys/types.h>
#include <sys/stat.h>
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
    int red;
} ULAZNI_ARG;

int n, m;
double** matrica;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
double min = INT_MAX*1.0;

void* funkcija_niti(void* arg) {
    ULAZNI_ARG* ulaz = (ULAZNI_ARG*)arg;

    double min_reda = INT_MAX*1.0;
    for(int i = 0; i < m; i++) {
        if(matrica[ulaz->red][i] < min_reda) {
            min_reda = matrica[ulaz->red][i];
        }
    }

    provera_greske_niti(pthread_mutex_lock(&mutex), "");
    if(min_reda < min) {
        min = min_reda;
    }
    provera_greske_niti(pthread_mutex_unlock(&mutex), "");

    return NULL;
}

int main(int argc, char** argv) {
    
    provera_greske(argc == 2, "");

    FILE* ulaz = fopen(argv[1], "r");
    provera_greske(ulaz != NULL, "");

    fscanf(ulaz, "%d%d", &n, &m);
    matrica = (double**)malloc(n*sizeof(double*));
    provera_greske(matrica != NULL, "");
    for(int i = 0; i < n; i++) {
        matrica[i] = (double*)malloc(m*sizeof(double));
        provera_greske(matrica[i] != NULL, "");
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            fscanf(ulaz, "%lf", &matrica[i][j]);
        }
    }

    pthread_t* niti = (pthread_t*)malloc(n*sizeof(pthread_t));
    provera_greske(niti != NULL, "");

    ULAZNI_ARG* argumenti = (ULAZNI_ARG*)malloc(n*sizeof(ULAZNI_ARG));
    provera_greske(argumenti != NULL, "");

    for(int i = 0; i < n; i++) {
        argumenti[i].red = i;
        provera_greske_niti(pthread_create(&niti[i], NULL, funkcija_niti, &argumenti[i]), "");
    }
    for(int i = 0; i < n; i++) {
        provera_greske_niti(pthread_join(niti[i], NULL), "");
    }

    fprintf(stdout, "%lf\n", min);

    free(niti);
    free(argumenti);
    for(int i = 0; i < n; i++) {
        free(matrica[i]);
    }
    free(matrica);
    fclose(ulaz);
    exit(EXIT_SUCCESS);
}