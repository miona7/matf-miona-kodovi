#define _XOPEN_SOURCE (700)
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include <semaphore.h>

#define provera_greske(uslov, poruka) \
    do { \
        if(!(uslov)) { \
            fprintf(stderr, "%s\n", poruka); \
            exit(EXIT_FAILURE); \
        } \
    } while(0)

#define ARRAY_MAX (1024)

typedef struct {
    sem_t inDataReady;
    int array[ARRAY_MAX];
    unsigned arrayLen;
} OsData;

bool sadrzi_bar_4_jedinice(int x) {
    int brojac = 0;
    while(x) {
        x &= (x-1);
        brojac++;
    }
    return brojac >= 4;
}

void* otvori_deljenu_memoriju(const char* ime, unsigned* velicina) {
    int shm_fd = shm_open(ime, O_RDWR, 0600);
    provera_greske(shm_fd != -1, "");

    struct stat fInfo;
    provera_greske(fstat(shm_fd, &fInfo) != -1, "");
    *velicina = fInfo.st_size;

    void* adresa = mmap(NULL, *velicina, PROT_WRITE | PROT_READ, MAP_SHARED, shm_fd, 0);
    provera_greske(adresa != MAP_FAILED, "");

    close(shm_fd);
    return adresa;
}

int main(int argc, char** argv) {
    
    provera_greske(argc == 3, "");

    unsigned velicina = 0;
    OsData* ulazna_dm = otvori_deljenu_memoriju(argv[1], &velicina);

    unsigned velicina1 = 0;
    OsData* izlazna_dm = otvori_deljenu_memoriju(argv[2], &velicina1);
    
    int niz[ARRAY_MAX]; int n = ulazna_dm->arrayLen;
    provera_greske(sem_wait(&(ulazna_dm->inDataReady)) != -1, "");
    for(int i = 0; i < n; i++) {
        niz[i] = ulazna_dm->array[i];
    }
    //provera_greske(sem_post(&(ulazna_dm->inDataReady)) != -1, "");
    provera_greske(sem_post(&(izlazna_dm->inDataReady)) != -1, "");
    provera_greske(munmap(ulazna_dm, velicina) != -1, "");


    provera_greske(sem_wait(&(izlazna_dm->inDataReady)) != -1, "");
    int k = 0;
    for(int i = 0; i < n; i++) {
        if(sadrzi_bar_4_jedinice(niz[i])) {
            izlazna_dm->array[k++] = niz[i];
        }
    }    
    izlazna_dm->arrayLen = k;
    provera_greske(sem_post(&(izlazna_dm->inDataReady)) != -1, "");
    
    //provera_greske(munmap(izlazna_dm, velicina1) != -1, "");

    exit(EXIT_SUCCESS);
}