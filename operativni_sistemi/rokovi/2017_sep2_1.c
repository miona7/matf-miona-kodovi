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

#define MAX (2048)

typedef struct {
    char* putanja;
    int pocetak;
    int duzina;
} ULAZNI_ARG;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int kodoni[MAX];
int duzina = 0;

char* kodon1 = "tag";
char* kodon2 = "taa";
char* kodon3 = "tga";

void* funkcija_niti(void* arg) {
    ULAZNI_ARG* ulaz = (ULAZNI_ARG*)arg;

    int fd = open(ulaz->putanja, O_RDONLY);
    provera_greske(fd != -1, "");
    provera_greske(lseek(fd, ulaz->pocetak, SEEK_SET) != (off_t)-1, "");

    char bafer[ulaz->duzina + 1];
    provera_greske(read(fd, bafer, ulaz->duzina) != -1, "");
    bafer[ulaz->duzina] = '\0';

    int pozicije[MAX];
    int p = 0;
    for(int i = 0; i < ulaz->duzina; i++) {
        if(strncmp(&bafer[i], kodon1, 3) == 0 || strncmp(&bafer[i], kodon2, 3) == 0 || strncmp(&bafer[i], kodon3, 3) == 0) {
            pozicije[p++] = ulaz->pocetak + i;
        }
    }

    provera_greske_niti(pthread_mutex_lock(&mutex), "");
    for(int i = 0; i < p; i++) {
        kodoni[duzina++] = pozicije[i];
    }
    provera_greske_niti(pthread_mutex_unlock(&mutex), "");

    close(fd);
    return NULL;
}

int main(int argc, char** argv) {
    
    provera_greske(argc == 3, "");

    struct stat fInfo;
    provera_greske(stat(argv[2], &fInfo) != -1, "");

    int n = strtol(argv[1], NULL, 10);
    char* putanja = argv[2];
    int m = fInfo.st_size;

    pthread_t* niti = (pthread_t*)malloc(n*sizeof(pthread_t));
    provera_greske(niti != NULL, "");

    ULAZNI_ARG* argumenti = (ULAZNI_ARG*)malloc(n*sizeof(ULAZNI_ARG));
    provera_greske(argumenti != NULL, "");

    for(int i = 0; i < n; i++) {
        argumenti[i].putanja = putanja;
        argumenti[i].pocetak = i*(m/n);
        argumenti[i].duzina = m/n;
        provera_greske_niti(pthread_create(&niti[i], NULL, funkcija_niti, &argumenti[i]), "");
    }

    for(int i = 0; i < n; i++) {
        provera_greske_niti(pthread_join(niti[i], NULL), "");
    }

    for(int i = 0; i < duzina; i++) {
        fprintf(stdout, "%d ", kodoni[i]);
    }
    fprintf(stdout, "\n");

    free(niti);
    free(argumenti);
    exit(EXIT_SUCCESS);
} 