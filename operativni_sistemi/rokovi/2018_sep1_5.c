#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include <semaphore.h>
#include <signal.h>

#define provera_greske(uslov, poruka) \
    do { \
        if(!(uslov)) { \
            fprintf(stderr, "%s\n", poruka); \
            exit(EXIT_FAILURE); \
        } \
    } while(0)

#define ARRAY_MAX (1024)
#define PRAVA (0600)

typedef struct {
    sem_t dataProcessingFinished;
    int array[ARRAY_MAX];
    unsigned arrayLen;
} OsInputData;

int sigusr1 = 0;
int sigusr2 = 0;

void rukovaoc_signalom(int sig) {
    switch(sig) {
        case SIGUSR1:
            sigusr1 = 1;
            break;
        case SIGUSR2:
            sigusr2 = 1;
            break;
    }
}

void* otvori_deljenu_memoriju(const char* ime, unsigned* velicina) {
    int shm_fd = shm_open(ime, O_RDWR, PRAVA);
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
    OsInputData* dm = (OsInputData*)otvori_deljenu_memoriju(argv[1], &velicina);

    provera_greske(signal(SIGUSR1, rukovaoc_signalom) != SIG_ERR, "");
    provera_greske(signal(SIGUSR2, rukovaoc_signalom) != SIG_ERR, "");
    pause();

    if(sigusr1) {
        for(unsigned i = 0; i < dm->arrayLen; i++) {
            dm->array[i] = -dm->array[i];
        }
        sigusr1 = 0;
    } 
    if(sigusr2) {
        for(unsigned i = 0; i < dm->arrayLen; i++) {
            dm->array[i] *= 2;
        }
        sigusr2 = 0;
    }
    provera_greske(sem_post(&(dm->dataProcessingFinished)) != -1, "");

    provera_greske(munmap(dm, velicina) != -1, "");
    exit(EXIT_SUCCESS);
}