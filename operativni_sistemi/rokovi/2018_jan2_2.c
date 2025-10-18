#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

#include <sys/stat.h>
#include <sys/types.h>
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

#define KORAK (10)

typedef struct {
    double x;
    double y;
} TACKA;

typedef struct {
    int br_niti;
} ULAZNI_ARG;

TACKA* tacke;
int n;
double min_rastojanje = LONG_MAX;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* funkcija_niti(void* arg) {
    ULAZNI_ARG* ulaz = (ULAZNI_ARG*)arg;

    for(int i = 0; i < n; i++) {
        if(i != ulaz->br_niti) {
            double rastojanje = (tacke[i].x - tacke[ulaz->br_niti].x)*(tacke[i].x - tacke[ulaz->br_niti].x) + (tacke[i].y - tacke[ulaz->br_niti].y)*(tacke[i].y - tacke[ulaz->br_niti].y);
            rastojanje = sqrt(rastojanje);

            provera_greske_niti(pthread_mutex_lock(&mutex), "");
            if(rastojanje < min_rastojanje) {
                min_rastojanje = rastojanje;
            }
            provera_greske_niti(pthread_mutex_unlock(&mutex), "");
        }
    }

    return NULL;
}

int main(int argc, char** argv) {

    tacke = (TACKA*)malloc(sizeof(TACKA));
    provera_greske(tacke != NULL, "");
    int alocirano = 1;

    int i = 0;
    while(fscanf(stdin, "%lf%lf", &tacke[i].x, &tacke[i].y) == 2) {
        if(i + 1 == alocirano) {
            alocirano *= KORAK;
            tacke = (TACKA*)realloc(tacke, alocirano*sizeof(TACKA));
            provera_greske(tacke != NULL, "");
        }
        i++;
    }
    n = i;

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

    fprintf(stdout, "%lf\n", min_rastojanje);

    free(niti);
    free(argumenti);
    free(tacke);
    exit(EXIT_SUCCESS);
} 