#include <stdio.h>
#include <stdlib.h>
#include <utime.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define provera_greske(uslov, poruka) \
    do { \
        if(!(uslov)) { \
            fprintf(stderr, "%s\n", poruka); \
            exit(EXIT_FAILURE); \
        } \
    } while(0)

int main(int argc, char** argv) {

    provera_greske(argc == 3, "");
    
    struct stat finfo;
    provera_greske(stat(argv[1], &finfo) != -1, "");

    struct utimbuf bafer;
    bafer.actime = atol(argv[2]);
    bafer.modtime = atol(argv[2]);

    provera_greske(utime(argv[1], &bafer) != -1, "");

    exit(EXIT_SUCCESS);
}