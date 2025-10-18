#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

#define MAX (256)

typedef struct {
    char* fajl;
} ULAZNI_ARG;

typedef struct {
    int br_reci;
} IZLAZNI_ARG;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int max_reci = 0;
char* max_fajl = NULL;

void* funkcija_niti(void* arg) {

    ULAZNI_ARG* ulaz = (ULAZNI_ARG*)arg;

    FILE* f = fopen(ulaz->fajl, "r");
    provera_greske(f != NULL, "");

    int brojac = 0; char rec[MAX];
    while(fscanf(f, "%s", rec) == 1) {
        brojac++;
    }
    fclose(f);

    provera_greske_niti(pthread_mutex_lock(&mutex), "");
    if(brojac > max_reci) {
        max_reci = brojac;
        max_fajl = ulaz->fajl;
    }
    provera_greske_niti(pthread_mutex_unlock(&mutex), "");

    IZLAZNI_ARG* izlaz = (IZLAZNI_ARG*)malloc(sizeof(IZLAZNI_ARG));
    provera_greske(izlaz != NULL, "");
    izlaz->br_reci = brojac;
    return izlaz;
}

int main(int argc, char** argv) {

    provera_greske(argc > 1, "");

    int br_niti = argc-1;
    pthread_t* niti = (pthread_t*)malloc(br_niti*sizeof(pthread_t));
    provera_greske(niti != NULL, "");

    ULAZNI_ARG* argumenti = (ULAZNI_ARG*)malloc(br_niti*sizeof(ULAZNI_ARG));
    provera_greske(argumenti != NULL, "");

    for(int i = 0; i < br_niti; i++) {
        argumenti[i].fajl = argv[i+1];
        provera_greske_niti(pthread_create(&niti[i], NULL, funkcija_niti, &argumenti[i]), "");
    }

    int ukupno_reci = 0;
    for(int i = 0; i < br_niti; i++) {
        IZLAZNI_ARG* rez = NULL;
        provera_greske_niti(pthread_join(niti[i], (void**)&rez), "");
        ukupno_reci += rez->br_reci;
        free(rez);
    }

    char* ime = strrchr(max_fajl, '/');
    fprintf(stdout, "%d %s\n", ukupno_reci, (ime != NULL ? ime + 1 : max_fajl));

    free(niti);
    free(argumenti);
    exit(EXIT_SUCCESS);
}
