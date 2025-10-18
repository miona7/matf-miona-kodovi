#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

typedef struct {
    char* putanja;
    char* w;
    int pocetak;
    int duzina;
} ULAZNI_ARG;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int suma = 0;

void* funkcija_niti(void* arg) {
    ULAZNI_ARG* ulaz = (ULAZNI_ARG*)arg;

    int fd = open(ulaz->putanja, O_RDONLY);
    provera_greske(fd != -1, "");

    provera_greske(lseek(fd, ulaz->pocetak, SEEK_SET) != (off_t)-1, "");
    
    char bafer[ulaz->duzina+1];
    provera_greske(read(fd, bafer, ulaz->duzina) != -1, "");
    bafer[ulaz->duzina] = '\0';
    close(fd);

    int zbir = 0;
    char* s = bafer;
    while((s = strstr(s, ulaz->w)) != NULL) {
        zbir++;
        s++;
    }

    provera_greske_niti(pthread_mutex_lock(&mutex), "");
    suma += zbir;
    provera_greske_niti(pthread_mutex_unlock(&mutex), "");

    return NULL;
}

int main(int argc, char** argv) {

    provera_greske(argc == 4, "");

    struct stat fInfo;
    provera_greske(stat(argv[1], &fInfo) != -1, "");
    int n = fInfo.st_size;
    char* putanja = argv[1];
    char* w = argv[2];
    int k = strtol(argv[3], NULL, 10);

    pthread_t* niti = (pthread_t*)malloc(k*sizeof(pthread_t));
    provera_greske(niti != NULL, "");

    ULAZNI_ARG* argumenti = (ULAZNI_ARG*)malloc(k*sizeof(ULAZNI_ARG));
    provera_greske(argumenti != NULL, "");

    for(int i = 0; i < k; i++) {
        argumenti[i].putanja = putanja;
        argumenti[i].w = w;
        argumenti[i].pocetak = i*(n/k);
        argumenti[i].duzina = n/k;
        provera_greske_niti(pthread_create(&niti[i], NULL, funkcija_niti, &argumenti[i]), "");
    }

    for(int i = 0; i < k; i++) {
        provera_greske_niti(pthread_join(niti[i], NULL), "");
    }

    fprintf(stdout, "%d\n", suma);

    free(niti);
    free(argumenti);
    exit(EXIT_SUCCESS);
}