#define _XOPEN_SOURCE (700)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <ftw.h>

#define provera_greske(uslov, poruka) \
    do { \
        if(!(uslov)) { \
            fprintf(stderr, "%s\n", poruka); \
            exit(EXIT_FAILURE); \
        } \
    } while(0)

char* pocetak = "test_";

int obidji_dir(const char* putanja, const struct stat* fb, int typeflag, struct FTW* ftwbuf) {

    if(S_ISDIR(fb->st_mode)) {
        if(strncmp(putanja + ftwbuf->base, pocetak, strlen(pocetak)) == 0) {
            if(!(fb->st_mode & S_IWGRP) && !(fb->st_mode & S_IWOTH)) {
                fprintf(stdout, "%s\n", putanja + ftwbuf->base);
            }
        }
    }

    return 0;
}

int main(int argc, char** argv) {

    provera_greske(argc == 2, "");
    struct stat fInfo;
    provera_greske(stat(argv[1], &fInfo) != -1, "");
    provera_greske(S_ISDIR(fInfo.st_mode), "");

    provera_greske(nftw(argv[1], obidji_dir, 50, 0) != -1, "");

    exit(EXIT_SUCCESS);
} 