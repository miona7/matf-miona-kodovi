#define _XOPEN_SOURCE (700)
#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#define provera_greske(uslov, poruka) \
    do { \
        if(!(uslov)) { \
            fprintf(stderr, "%s\n", poruka); \
            exit(EXIT_FAILURE); \
        } \
    } while(0)

#define MAX (1024)

int main(int argc, char** argv) {

    provera_greske(argc == 2, "");

    struct stat fInfo;
    provera_greske(lstat(argv[1], &fInfo) != -1, "");
    provera_greske(S_ISLNK(fInfo.st_mode), "");
    
    char bafer[MAX+1];
    int procitano = readlink(argv[1], bafer, MAX);
    provera_greske(procitano != -1, "");
    bafer[procitano] = '\0';
    fprintf(stdout, "%s\n", bafer);

    exit(EXIT_SUCCESS);
}