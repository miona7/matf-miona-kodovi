#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <pthread.h>
#include <unistd.h>
#include <fcntl.h>
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
    
typedef struct {
    int pocetak;
} ULAZNI_ARG;

typedef struct {
    float norma;
} IZLAZNI_ARG;

int m, n, k;
float** vektor;

void* funkcija_niti(void* arg) {

    ULAZNI_ARG* ulaz = (ULAZNI_ARG*)arg;

    float max_norma = -1;
    for(int i = 0; i < m/k; i++) {
        float norma = 0.0;
        for(int j = 0; j < n; j++) {
            norma += vektor[i+ulaz->pocetak][j]*vektor[i+ulaz->pocetak][j];
        }
        norma = sqrt(norma);
        if(norma > max_norma) {
            max_norma = norma;
        }
    }

    IZLAZNI_ARG* izlaz = (IZLAZNI_ARG*)malloc(sizeof(IZLAZNI_ARG));
    provera_greske(izlaz != NULL, "");
    izlaz->norma = max_norma;
    return izlaz;
}

int main(int argc, char** argv) {

    fscanf(stdin, "%d%d%d", &m, &n, &k);
    vektor = (float**)malloc(m*sizeof(float*));
    provera_greske(vektor != NULL, "");
    for(int i = 0; i < m; i++) {
        vektor[i] = (float*)malloc(n*sizeof(float));
        provera_greske(vektor[i] != NULL, "");
    }

    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            fscanf(stdin, "%f", &vektor[i][j]);
        }
    }

    pthread_t* niti = (pthread_t*)malloc(k*sizeof(pthread_t));
    provera_greske(niti != NULL, "");

    ULAZNI_ARG* argumenti = (ULAZNI_ARG*)malloc(k*sizeof(ULAZNI_ARG));
    provera_greske(argumenti != NULL, "");

    for(int i = 0; i < k; i++) {
        argumenti[i].pocetak = i*(m/k);
        provera_greske_niti(pthread_create(&niti[i], NULL, funkcija_niti, &argumenti[i]), "");
    }

    float max = -1; int br_niti = -1;
    for(int i = 0; i < k; i++) {
        IZLAZNI_ARG* rez = NULL;
        provera_greske_niti(pthread_join(niti[i], (void**)&rez), "");

        if(rez->norma > max) {
            max = rez->norma;
            br_niti = i;
        }

        free(rez);
    }

    fprintf(stdout, "%d %f\n", br_niti, max);

    free(argumenti);
    free(niti);
    for(int i = 0; i < m; i++) {
        free(vektor[i]);
    }
    free(vektor);
    exit(EXIT_SUCCESS);
}