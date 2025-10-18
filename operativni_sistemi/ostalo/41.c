#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

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
    provera_greske(stat(argv[1], &fInfo) != -1, "");
    provera_greske(!S_ISDIR(fInfo.st_mode), "");

    struct stat lInfo;
    provera_greske(lstat(argv[1], &lInfo) != -1, "");

    fprintf(stdout, "%ld\n", fInfo.st_size - lInfo.st_size);

    exit(EXIT_SUCCESS);
}