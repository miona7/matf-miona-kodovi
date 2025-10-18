#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
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

char* ext = NULL;

int pronadji_fajl(const char* fPath, const struct stat* fInfo, int typeflag, struct FTW* buf) {

    if(typeflag == FTW_F && (buf->level >= 2 && buf->level <= 5)) {
        char* ekstenzija = strrchr(fPath + buf->base, '.');
        if(ekstenzija != NULL && strcmp(ekstenzija, ext) == 0) {
            fprintf(stdout, "%s ", fPath + buf->base);
        }
    }
    return 0;
}

int main(int argc, char** argv) {

    provera_greske(argc == 3, "");

    struct stat fInfo;
    provera_greske(stat(argv[1], &fInfo) != -1, "");
    provera_greske(S_ISDIR(fInfo.st_mode), "");

    ext = argv[2];
    provera_greske(nftw(argv[1], pronadji_fajl, MAX, FLAG) != -1, "");
    fprintf(stdout, "\n");

    exit(EXIT_SUCCESS);
}