#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
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

int n;
int** matrica;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int max = -1;
int br_cvora = -1;

void* funkcija_niti(void* arg) {
    ULAZNI_ARG* ulaz = (ULAZNI_ARG*)arg;

    int stepen = 0;
    for(int i = 0; i < n; i++) {
        stepen += matrica[i][ulaz->br_niti];
    }

    provera_greske_niti(pthread_mutex_lock(&mutex), "");
    if(stepen > max) {
        max = stepen;
        br_cvora = ulaz->br_niti;
    }
    provera_greske_niti(pthread_mutex_unlock(&mutex), "");

    return NULL;
}

int main(int argc, char** argv) {

    fscanf(stdin, "%d", &n);
    
    matrica = (int**)malloc(n*sizeof(int*));
    provera_greske(matrica != NULL, "");
    for(int i = 0; i < n; i++) {
        matrica[i] = (int*)malloc(n*sizeof(int));
        provera_greske(matrica[i] != NULL, "");
    }

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            fscanf(stdin, "%d", &matrica[i][j]);
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

    fprintf(stdout, "%d\n", br_cvora);

    free(niti);
    free(argumenti);
    for(int i = 0; i < n; i++) {
        free(matrica[i]);
    }
    free(matrica);
    exit(EXIT_SUCCESS);
}