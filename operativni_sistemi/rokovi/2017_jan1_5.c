#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>

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
    float array[ARRAY_MAX];
    unsigned arrayLen;
} OsInputData;

int sortiraj(const void* x, const void* y) {
    float a = *((float*)x);
    float b = *((float*)y);

    if(a <= b) {
        return -1;
    } else {
        return 1;
    }
}

void* otvori_deljeni_blok_memorije(const char* putanja, unsigned* velicina) {
    int shm_fd = shm_open(putanja, O_RDWR, 0600);
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
    OsInputData* d = otvori_deljeni_blok_memorije(argv[1], &velicina);

    provera_greske(sem_wait(&(d->inDataReady)) != -1, "");

    qsort(d->array, d->arrayLen, sizeof(float), sortiraj);
    fprintf(stdout, "%f\n", d->array[d->arrayLen/2]);   
    
    provera_greske(munmap(d, velicina) != -1, "");    
    exit(EXIT_SUCCESS);
}