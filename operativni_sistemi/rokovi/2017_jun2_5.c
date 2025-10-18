#include <stdio.h>
#include <stdlib.h>

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
} OsInputData;

int broj_jedinica(int n) {
    int brojac = 0;
    while(n) {
        brojac++;
        n &= (n-1);
    }
    return brojac;
}

void* otvori_deljeni_deo_memorije(const char* ime, unsigned* velicina) {
    int shm_fd = shm_open(ime, O_RDWR, 0600);
    provera_greske(shm_fd != -1, "");

    struct stat fInfo;
    provera_greske(fstat(shm_fd, &fInfo) != -1, "");
    *velicina = fInfo.st_size;

    void* adresa = mmap(NULL, *velicina, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    provera_greske(adresa != MAP_FAILED, "");

    close(shm_fd);
    return adresa;
}

int main(int argc, char** argv) {

    provera_greske(argc == 2, "");

    unsigned velicina = 0;
    OsInputData* dm = (OsInputData*)otvori_deljeni_deo_memorije(argv[1], &velicina);

    provera_greske(sem_wait(&(dm->inDataReady)) != -1, "");
    for(unsigned i = 0; i < dm->arrayLen; i++) {
        if(broj_jedinica(dm->array[i]) >= 4) {
            fprintf(stdout, "%d ", dm->array[i]);
        }
    }
    fprintf(stdout, "\n");

    provera_greske(munmap(dm, velicina) != -1, "");
    exit(EXIT_SUCCESS);
}