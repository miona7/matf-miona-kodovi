#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define SEKUNDE_U_SATU (60*60)

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

    double razlika = fInfo.st_atime-fInfo.st_mtime;

    fprintf(stdout, "%d\n", (int)(razlika/SEKUNDE_U_SATU + 1));   

    exit(EXIT_SUCCESS);
}