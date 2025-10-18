#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include <sys/types.h>
#include <sys/stat.h>
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
    int vrsta;
    int kolona;
} ULAZNI_ARG;

int n, m, k;
int** matrica1;
int** matrica2;
int** matrica3;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int max = INT_MIN;

void* funkcija_niti(void* arg) {
    ULAZNI_ARG* ulaz = (ULAZNI_ARG*)arg;

    int rez = 0;

    for(int i = 0; i < m; i++) {
        rez += matrica1[ulaz->vrsta][i] * matrica2[i][ulaz->kolona];
    }

    provera_greske_niti(pthread_mutex_lock(&mutex), "");
    matrica3[ulaz->vrsta][ulaz->kolona] = rez;
    if(rez > max) {
        max = rez;
    }
    provera_greske_niti(pthread_mutex_unlock(&mutex), "");

    return NULL;
}

int main(int argc, char** argv) {

    fscanf(stdin, "%d%d", &n, &m);
    matrica1 = (int**)malloc(n*sizeof(int*));
    provera_greske(matrica1 != NULL, "");
    for(int i = 0; i < n; i++) {
        matrica1[i] = (int*)malloc(m*sizeof(int));
        provera_greske(matrica1[i] != NULL, "");
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            fscanf(stdin, "%d", &matrica1[i][j]);
        }
    }

    fscanf(stdin, "%d%d", &m, &k);
    matrica2 = (int**)malloc(m*sizeof(int*));
    provera_greske(matrica2 != NULL, "");
    for(int i = 0; i < m; i++) {
        matrica2[i] = (int*)malloc(k*sizeof(int));
        provera_greske(matrica2[i] != NULL, "");
    }
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < k; j++) {
            fscanf(stdin, "%d", &matrica2[i][j]);
        }
    }

    matrica3 = (int**)malloc(n*sizeof(int*));
    provera_greske(matrica3 != NULL, "");
    for(int i = 0; i < n; i++) {
        matrica3[i] = (int*)malloc(k*sizeof(int));
        provera_greske(matrica3[i] != NULL, "");
    }

    pthread_t* niti = (pthread_t*)malloc((n*k)*sizeof(pthread_t));
    provera_greske(niti != NULL, "");

    ULAZNI_ARG* argumenti = (ULAZNI_ARG*)malloc((n*k)*sizeof(ULAZNI_ARG));
    provera_greske(argumenti != NULL, "");

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < k; j++) {
            argumenti[i*k + j].vrsta = i;
            argumenti[i*k + j].kolona = j;
            provera_greske_niti(pthread_create(&niti[i*k + j], NULL, funkcija_niti, &argumenti[i*k + j]), "");
        }
    }

    for(int i = 0; i < n*k; i++) {
        provera_greske_niti(pthread_join(niti[i], NULL), "");
    }

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < k; j++) {
            fprintf(stdout, "%d ", matrica3[i][j]);
        }
        fprintf(stdout, "\n");
    }
    fprintf(stdout, "%d\n", max);

    free(niti);
    free(argumenti);
    for(int i = 0; i < n; i++) {
        free(matrica1[i]);
    }
    free(matrica1);
    for(int i = 0; i < m; i++) {
        free(matrica2[i]);
    }
    free(matrica2);
    for(int i = 0; i < n; i++) {
        free(matrica3[i]);
    }
    free(matrica3);
    exit(EXIT_SUCCESS);
}