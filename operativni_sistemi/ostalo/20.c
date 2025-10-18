#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define BROJ_SEKUNDI (24*60*60)

#define provera_greske(uslov, poruka) \
    do { \
        if(!(uslov)) { \
            fprintf(stderr, "%s\n", poruka); \
            exit(EXIT_FAILURE); \
        } \
    } while(0)

int main(int argc, char** argv) {

    provera_greske(argc == 3, "");

    struct stat fInfo1;
    provera_greske(stat(argv[1], &fInfo1) != -1, "");

    struct stat fInfo2;
    provera_greske(stat(argv[2], &fInfo2) != -1, "");
    
    printf("%d\n", (int)ceil(abs((int)fInfo1.st_mtime - (int)fInfo2.st_mtime)/(double)BROJ_SEKUNDI));

    exit(EXIT_SUCCESS);
}
