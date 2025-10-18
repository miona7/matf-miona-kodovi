#define _XOPEN_SOURCE (700)
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>

#define provera_greske(uslov, poruka) \
    do { \
        if(!(uslov)) { \
            fprintf(stderr, "%s\n", poruka); \
            exit(EXIT_FAILURE); \
        } \
    } while(0)

#define MAX (7)

char* dani[MAX] = { "nedelja", "ponedeljak", "utorak", "sreda", "cetvrtak", "petak", "subota" };

int main(int argc, char** argv) {
    
    provera_greske(argc == 3, "");

    time_t sekunde = atol(argv[1]);
    struct tm* vreme = localtime(&sekunde);
    provera_greske(vreme != NULL, "");

    fprintf(stdout, "%s ", dani[vreme->tm_wday]);

    vreme->tm_year += atoi(argv[2]);
    sekunde = mktime(vreme);
    provera_greske(sekunde != (time_t)-1, "");

    vreme = localtime(&sekunde);
    provera_greske(vreme != NULL, "");

    fprintf(stdout, "%s\n", dani[vreme->tm_wday]);

    exit(EXIT_SUCCESS);
}
