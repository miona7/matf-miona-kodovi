#define _XOPEN_SOURCE (700)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

#define provera_greske_niti(gr, poruka) \
    do { \
        int greska = gr; \
        if(greska) { \
            errno = greska; \
            provera_greske(0, poruka); \
        } \
    } while(0)

#define PRAVA (0777)

int main(int argc, char** argv) {
    
    provera_greske(argc == 4, "");

    FILE* ulaz = fopen(argv[1], "r");
    provera_greske(ulaz != NULL, "");

    int a = strtol(argv[2], NULL, 10);
    int b = strtol(argv[3], NULL, 10);

    provera_greske(fseek(ulaz, a, SEEK_SET) != -1, "fseek");

    char* naziv = (char*)malloc((b+1)*sizeof(char));
    provera_greske(naziv != NULL, "malloc");
    fscanf(ulaz, "%s", naziv);

    char* naziv1 = (char*)malloc((b+1)*sizeof(char));
    provera_greske(naziv1 != NULL, "malloc");
    snprintf(naziv1, b+1, "%s", naziv);

    provera_greske(mkdir(naziv1, PRAVA) != -1, "mkdir");
    provera_greske(chmod(naziv1, PRAVA) != -1, "chmod");

    free(naziv);
    free(naziv1);
    fclose(ulaz);
    exit(EXIT_SUCCESS);
}
