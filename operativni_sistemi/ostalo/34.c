#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <ftw.h>

#define MAX (50)

#define provera_greske(uslov, poruka) \
    do { \
        if(!(uslov)) { \
            fprintf(stderr, "%s\n", poruka); \
            exit(EXIT_FAILURE); \
        } \
    } while(0)

int br_reg = 0;
int br_dir = 0;
int br_kar = 0;
int br_bl = 0;
int br_link = 0;
int br_fifo = 0;
int br_sok = 0;
int br_uk = 0;

int obidji_dir(const char* putanja, const struct stat* sb, int typeflag, struct FTW* ftwbuf) {
    
    switch (sb->st_mode & S_IFMT) {
        case S_IFBLK: 
            br_bl++;
            br_uk++;
            break;
        case S_IFCHR:
            br_kar++;
            br_uk++;
            break;
        case S_IFDIR:
            br_dir++;
            br_uk++;
            break;
        case S_IFIFO:
            br_fifo++;
            br_uk++;
            break;
        case S_IFLNK:
            br_link++;
            br_uk++;
            break;
        case S_IFREG:
            br_reg++;
            br_uk++;
            break;
        case S_IFSOCK:
            br_sok++;
            br_uk++;
            break;
        default:
            provera_greske(0, "");
            break;
    }

    return 0;
}

int main(int argc, char** argv) {

    provera_greske(argc == 2, "");

    struct stat fInfo;
    provera_greske(stat(argv[1], &fInfo) != -1, "");
    provera_greske(S_ISDIR(fInfo.st_mode), "");

    provera_greske(nftw(argv[1], obidji_dir, MAX, FTW_PHYS) != -1, "");

    fprintf(stdout, "%d %d %d %d %d %d %d %d\n", br_reg, br_dir, br_kar, br_bl, br_link, br_fifo, br_sok, br_uk);

    exit(EXIT_SUCCESS);
}