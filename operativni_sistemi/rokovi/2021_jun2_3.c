#define _XOPEN_SOURCE (700)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <pthread.h>
#include <semaphore.h>

#define provera_greske(uslov, poruka) \
    do { \
        if(!(uslov)) { \
            fprintf(stderr, "%s\n", poruka); \
            exit(EXIT_FAILURE); \
        } \
    } while(0)

#define ARRAY_MAX (1024)
#define MOD (0600)

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

void* otvori_blok_deljene_mem(const char* ime, unsigned* velicina) {
    int shm_fd = shm_open(ime, O_RDWR, MOD);
    provera_greske(shm_fd != -1, "");

    struct stat f_info;
    provera_greske(fstat(shm_fd, &f_info) != -1, "");
    *velicina = f_info.st_size;

    void* adresa = mmap(NULL, *velicina, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    provera_greske(adresa != MAP_FAILED, "");

    close(shm_fd);
    return adresa;
}

int main(int argc, char** argv) {
    
    provera_greske(argc == 3, "");

    unsigned velicina = 0;
    OsData* ulazna_mem = (OsData*)otvori_blok_deljene_mem(argv[1], &velicina);

    unsigned velicina1 = 0;
    OsData* izlazna_mem = (OsData*)otvori_blok_deljene_mem(argv[2], &velicina1);

    provera_greske(sem_wait(&(ulazna_mem->inDataReady)) != -1, "");
    izlazna_mem->arrayLen = 0;
    for(unsigned i = 0; i < ulazna_mem->arrayLen; i++) {
        if(sadrzi_bar_4_jedinice(ulazna_mem->array[i])) {
            izlazna_mem->array[izlazna_mem->arrayLen++] = ulazna_mem->array[i];
        }
    }
    provera_greske(sem_post(&(izlazna_mem->inDataReady)) != -1, "");

    provera_greske(munmap(ulazna_mem, velicina) != -1, "");
    exit(EXIT_SUCCESS);
}
