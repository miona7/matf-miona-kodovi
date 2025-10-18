#define _XOPEN_SOURCE (700)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <pthread.h>
#include <semaphore.h>
#include <ftw.h>

#define provera_greske(uslov, poruka) \
    do { \
        if(!(uslov)) { \
            fprintf(stderr, "%s\n", poruka); \
            exit(EXIT_FAILURE); \
        } \
    } while(0)

#define MAX (7)

char* dani[MAX] = {"nedelja", "ponedeljak", "utorak", "sreda", "cetvrtak", "petak", "subota"};

int obidji_dir(const char* ime, const struct stat* sb, int typeflag, struct FTW* ftwbuf) {

    if(S_ISREG(sb->st_mode)) {
        struct tm* vreme = localtime(&(sb->st_mtime));
        provera_greske(vreme != NULL, "");

        char* putanja = NULL;
        provera_greske((putanja = realpath(ime, putanja)) != NULL, "");
        fprintf(stdout, "%s %s\n", putanja, dani[vreme->tm_wday]);
    }

    return 0;
}

int main(int argc, char** argv) {
    
    provera_greske(argc == 2, "");

    struct stat f_info;
    provera_greske(stat(argv[1], &f_info) != -1, "");
    provera_greske(S_ISDIR(f_info.st_mode), "");

    provera_greske(nftw(argv[1], obidji_dir, 50, 0) != -1, "");

    exit(EXIT_SUCCESS);
}
