#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define SEKUNDE_U_DANU (24*60*60)

#define provera_greske(uslov, poruka) \
    do { \
        if(!(uslov)) { \
            fprintf(stderr, "%s\n", poruka); \
            exit(EXIT_FAILURE); \
        } \
    } while(0)

int main(int argc, char** argv) {

    provera_greske(argc == 2, "");

    struct stat fInfo;
    provera_greske(stat(argv[1], &fInfo) != -1, "Nepostojeci fajl");

    if(S_ISDIR(fInfo.st_mode)) {
        fprintf(stderr, "%s je direktorijum", argv[1]);
        provera_greske(0, "");
    }

    time_t vreme = fInfo.st_atime - fInfo.st_mtime;
    fprintf(stdout, "%u\n", (unsigned)vreme/SEKUNDE_U_DANU);

    exit(EXIT_SUCCESS);
}