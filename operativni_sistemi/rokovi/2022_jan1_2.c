#define _XOPEN_SOURCE (700)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <sys/types.h>
#include <sys/stat.h>
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

#define SEKUNDE_U_DANU (24*60*60)

char* ext = NULL;
time_t sada = 0;

int obidji_dir(const char* putanja, const struct stat* sb, int typeflag, struct FTW* ftwbuf) {

    if(typeflag == FTW_F) {
        int razlika = difftime(sada, sb->st_mtime) / SEKUNDE_U_DANU;
        if(razlika <= 7) {
            char* s = strrchr(putanja + ftwbuf->base, '.');
            if(s != NULL && strcmp(s, ext) == 0) {
                fprintf(stdout, "%s\n", putanja + ftwbuf->base);
            }
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
    provera_greske(time(&sada) != (time_t)-1, "");
    provera_greske(nftw(argv[1], obidji_dir, 50, 0) != -1, "");

    exit(EXIT_SUCCESS);
}