#include <stdio.h>
#include <stdlib.h>

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

int m, n, k;
float** vektori;

typedef struct {
    int pocetak;
} ULAZNI_ARG;

typedef struct {
    float lokalni_max;
} IZLAZNI_ARG;

void* funkcija_niti(void* arg) {
    ULAZNI_ARG* ulaz = (ULAZNI_ARG*)arg;

    float lokalni_max = -1.0;
    for(int i = 0; i < m/k; i++) {
        float sp = 0.0;
        for(int j = 0; j < n; j++) {
            sp += vektori[i+ulaz->pocetak][j]*vektori[m][j];
        }
        if(sp > lokalni_max) {
            lokalni_max = sp;
        }
    }
    
    IZLAZNI_ARG* izlaz = (IZLAZNI_ARG*)malloc(sizeof(IZLAZNI_ARG));
    provera_greske(izlaz != NULL, "");
    izlaz->lokalni_max = lokalni_max;
    return izlaz;
}

int main(int argc, char** argv) {

    fscanf(stdin, "%d%d%d", &m, &n, &k);
    
    vektori = (float**)malloc((m+1)*sizeof(float*));
    provera_greske(vektori != NULL, "");
    for(int i = 0; i <= m; i++) {
        vektori[i] = (float*)malloc(n*sizeof(float));
        provera_greske(vektori[i] != NULL, "");
    }

    for(int i = 0; i <= m; i++) {
        for(int j = 0; j < n; j++) {
            fscanf(stdin, "%f", &vektori[i][j]);
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

    float max = -1.0; int br_niti = -1;
    for(int i = 0; i < k; i++) {
        IZLAZNI_ARG* rez = NULL;
        provera_greske_niti(pthread_join(niti[i], (void**)&rez), "");
        if(rez->lokalni_max > max) {
            max = rez->lokalni_max;
            br_niti = i+1;
        }
        free(rez);
    }

    fprintf(stdout, "%d %f\n", br_niti, max);

    free(argumenti);
    free(niti);
    for(int i = 0; i <= m; i++) {
        free(vektori[i]);
    }
    free(vektori);
    exit(EXIT_SUCCESS);   
}