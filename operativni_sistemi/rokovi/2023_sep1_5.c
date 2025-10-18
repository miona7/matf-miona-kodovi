#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <semaphore.h>

#define provera_greske(uslov, poruka) \
    do { \
        if(!(uslov)) { \
            fprintf(stderr, "%s\n", poruka); \
            exit(EXIT_FAILURE); \
        } \
    } while(0)

#define MAX_SIZE (1024)
#define PRAVA (0600)

typedef struct {
    sem_t dataReady;
    sem_t operationDone;
    char array[MAX_SIZE];
    int resultSize;
    char result[MAX_SIZE];
} OsInputData;

void* otvori_deljenu_memoriju(const char* ime, unsigned* velicina) {
    int shm_fd = shm_open(ime, O_RDWR, PRAVA);
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
    
    provera_greske(argc == 2, "");

    unsigned velicina = 0;
    OsInputData* ulazna_dm = otvori_deljenu_memoriju(argv[1], &velicina);

    provera_greske(sem_wait(&(ulazna_dm->dataReady)) != -1, "");
    int n = sizeof(ulazna_dm->array) / sizeof(char);
    ulazna_dm->resultSize = 0;
    for(int i = 0; i < n; i++) {
        if(isdigit(ulazna_dm->array[i])) {
            ulazna_dm->result[ulazna_dm->resultSize++] = ulazna_dm->array[i];
        }
    }
    provera_greske(sem_post(&(ulazna_dm->operationDone)) != -1, "");

    provera_greske(munmap(ulazna_dm, velicina) != -1, "");
    exit(EXIT_SUCCESS);
}