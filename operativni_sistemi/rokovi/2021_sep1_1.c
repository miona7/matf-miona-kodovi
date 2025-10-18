#define _XOPEN_SOURCE (700)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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

#define MAX (12)

char* meseci[MAX] = { "januar", "februar", "mart", "april", "maj", "jun", "jul", "avgust", "septembar",
                        "oktobar", "novembar", "decembar" };

int main(int argc, char** argv) {
    
    provera_greske(argc == 2, "");

    time_t sekunde = atol(argv[1]);

    struct tm* vreme = localtime(&sekunde);
    provera_greske(vreme != NULL, "");

    fprintf(stdout, "%s ", meseci[vreme->tm_mon]);

    vreme->tm_mday += atoi(argv[2]);
    sekunde = mktime(vreme);
    provera_greske(sekunde != (time_t)-1, "");

    vreme = localtime(&sekunde);
    provera_greske(vreme != NULL, "");

    fprintf(stdout, "%s\n", meseci[vreme->tm_mon]);

    exit(EXIT_SUCCESS);
}
