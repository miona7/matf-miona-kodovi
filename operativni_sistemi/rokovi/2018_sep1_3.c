/*#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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

#define provera_greske_niti(greska, poruka) \
    do { \
        int gr = greska; \
        if(gr) { \
            errno = gr; \
            provera_greske(0, poruka); \
        } \
    } while(0)

typedef struct {
    double* vrsta;
    int n;
    double p;
} ULAZNI_ARG;

pthread_mutex_t semafor = PTHREAD_MUTEX_INITIALIZER;
double globalni_zbir = 0.0;

void* funkcija_niti(void* arg) {

    ULAZNI_ARG* ulaz = (ULAZNI_ARG*)arg;

    double norma = 0.0;
    for(int j = 0; j < ulaz->n; j++) {
        norma += pow(fabs(ulaz->vrsta[j]), ulaz->p);
    }

    provera_greske_niti(pthread_mutex_lock(&semafor), "");
    globalni_zbir += norma;
    provera_greske_niti(pthread_mutex_unlock(&semafor), "");

    /*IZLAZNI_ARG* izlaz = (IZLAZNI_ARG*)malloc(sizeof(IZLAZNI_ARG));
    provera_greske(izlaz != NULL, "");
    izlaz->norma = norma;

    return NULL;
}

int main(int argc, char** argv) {
    
    double p; int m; int n;
    fscanf(stdin, "%lf%d%d", &p, &m, &n);

    double** matrica = (double**)malloc(m*sizeof(double*));
    provera_greske(matrica != NULL, "");
    for(int i = 0; i < m; i++) {
        matrica[i] = (double*)malloc(n*sizeof(double));
        provera_greske(matrica[i] != NULL, "");
        for(int j = 0; j < n; j++) {
            fscanf(stdin, "%lf", &matrica[i][j]);
        }
    }

    pthread_t* niti = (pthread_t*)malloc(m*sizeof(pthread_t));
    provera_greske(niti != NULL, "");

    ULAZNI_ARG* arg = (ULAZNI_ARG*)malloc(m*sizeof(ULAZNI_ARG));
    provera_greske(arg != NULL, "");

    for(int i = 0; i < m; i++) {
        arg[i].vrsta = matrica[i];
        arg[i].n = n;
        arg[i].p = p;
        provera_greske_niti(pthread_create(&niti[i], NULL, funkcija_niti, (void*)&arg[i]), "");
    }

    for(int i = 0; i < m; i++) {
        //IZLAZNI_ARG* rez = NULL;
        provera_greske_niti(pthread_join(niti[i], NULL), "");
        //free(rez);
    }

    fprintf(stdout, "%lf\n", pow(globalni_zbir, 1/p));

    for(int i = 0; i < m; i++) {
        free(matrica[i]);
    }
    free(matrica);
    free(niti);
    free(arg);
    exit(EXIT_SUCCESS);
}*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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

#define provera_greske_niti(greska, poruka) \
    do { \
        int gr = greska; \
        if(gr) { \
            errno = gr; \
            provera_greske(0, poruka); \
        } \
    } while(0)

typedef struct {
    int br_niti;
} ULAZNI_ARG;

typedef struct {
    double norma;
} IZLAZNI_ARG;

double p;
int m, n;
double** matrica;

pthread_mutex_t semafor = PTHREAD_MUTEX_INITIALIZER;
double globalni_zbir = 0.0;

void* funkcija_niti(void* arg) {

    ULAZNI_ARG* ulaz = (ULAZNI_ARG*)arg;

    double norma = 0.0;
    int i = ulaz->br_niti;
    for(int j = 0; j < n; j++) {
        norma += pow(fabs(matrica[i][j]), p);
    }

    provera_greske_niti(pthread_mutex_lock(&semafor), "");
    globalni_zbir += norma;
    provera_greske_niti(pthread_mutex_unlock(&semafor), "");

    IZLAZNI_ARG* izlaz = (IZLAZNI_ARG*)malloc(sizeof(IZLAZNI_ARG));
    provera_greske(izlaz != NULL, "");
    izlaz->norma = norma;

    return izlaz;
}

int main(int argc, char** argv) {
    
    fscanf(stdin, "%lf%d%d", &p, &m, &n);

    matrica = (double**)malloc(m*sizeof(double*));
    provera_greske(matrica != NULL, "");
    for(int i = 0; i < m; i++) {
        matrica[i] = (double*)malloc(n*sizeof(double));
        provera_greske(matrica[i] != NULL, "");
    }

    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            fscanf(stdin, "%lf", &matrica[i][j]);
        }
    }

    pthread_t* niti = (pthread_t*)malloc(m*sizeof(pthread_t));
    provera_greske(niti != NULL, "");

    ULAZNI_ARG* arg = (ULAZNI_ARG*)malloc(m*sizeof(ULAZNI_ARG));
    provera_greske(arg != NULL, "");

    for(int i = 0; i < m; i++) {
        arg[i].br_niti = i;
        provera_greske_niti(pthread_create(&niti[i], NULL, funkcija_niti, &arg[i]), "");
    }

    for(int i = 0; i < m; i++) {
        IZLAZNI_ARG* rez = NULL;
        provera_greske_niti(pthread_join(niti[i], (void**)&rez), "");
        free(rez);
    }

    double r = pow(globalni_zbir, 1/p);
    fprintf(stdout, "%.4lf\n", r);

    for(int i = 0; i < m; i++) {
        free(matrica[i]);
    }
    free(matrica);
    free(niti);
    free(arg);
    exit(EXIT_SUCCESS);
}