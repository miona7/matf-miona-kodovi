#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <ftw.h>

#define MAX 50
#define FLAG 0

#define provera_greske(uslov, poruka) \
    do { \
        if(!(uslov)) { \
            fprintf(stderr, "%s\n", poruka); \
            exit(EXIT_FAILURE); \
        } \
    } while(0)

int pronadji_fajl(const char* fPath, const struct stat* fInfo, int typeflag, struct FTW* buf) {

    if(typeflag == FTW_D && buf->level >= 1 && buf->level <= 3 && strchr(fPath + buf->base, '.') != NULL) {
            fprintf(stdout, "%s ", fPath + buf->base);
    }
    
    return 0;
}

int main(int argc, char** argv) {

    provera_greske(argc == 2, "");

    struct stat fInfo;
    provera_greske(stat(argv[1], &fInfo) != -1, "");
    provera_greske(S_ISDIR(fInfo.st_mode), "");
    
    provera_greske(nftw(argv[1], pronadji_fajl, MAX, FTW_PHYS) != -1, "");

    exit(EXIT_SUCCESS);
}