#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAX (1024)

#define provera_greske(uslov, poruka) \
    do { \
        if(!(uslov)) { \
            fprintf(stderr, "%s\n", poruka); \
            exit(EXIT_FAILURE); \
        } \
    } while(0)

int main(int argc, char** argv) {

    provera_greske(argc >= 2, "");

    for(int i = 1; i < argc; i++) {
        struct stat fInfo;
        provera_greske(stat(argv[i], &fInfo) != -1, "");
        provera_greske(S_ISDIR(fInfo.st_mode), "");

        if(!(fInfo.st_mode & S_IROTH) && !(fInfo.st_mode & S_IWOTH) && !(fInfo.st_mode & S_IXOTH)) {
            char putanja[MAX];
            provera_greske(realpath(argv[i], putanja) != NULL, "");
            fprintf(stdout, "%ld\n", strlen(putanja));
        }
    }

    exit(EXIT_SUCCESS);
}