#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <libgen.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>

#define DANI_MODIFIKACIJE (5)
#define SEKUNDE_U_DANU (24*60*60)

#define provera_greske(uslov, poruka) \
    do { \
        if(!(uslov)) { \
            fprintf(stderr, "%s\n", poruka); \
            exit(EXIT_FAILURE); \
        } \
    } while(0)

void obidjiDir(char* putanja, time_t vreme_sad) {
    
    struct stat fInfo;
    provera_greske(lstat(putanja, &fInfo) != -1, "");

    if(S_ISREG(fInfo.st_mode)) {
        if((int)ceil(difftime(vreme_sad, fInfo.st_mtime)/(double)SEKUNDE_U_DANU) <= DANI_MODIFIKACIJE) {
            char* s = basename(putanja);
            fprintf(stdout, "%s\n", s);
        }
        return;
    }

    DIR* dir = opendir(putanja);
    provera_greske(dir != NULL, "");

    struct dirent* dirEnt = NULL;
    while((dirEnt = readdir(dir)) != NULL) {
        int n = strlen(putanja) + strlen(dirEnt->d_name) + 2;
        char* novaPutanja = (char*)malloc(n*sizeof(char));
        provera_greske(novaPutanja != NULL, "");

        sprintf(novaPutanja, "%s/%s", putanja, dirEnt->d_name);

        if(strcmp(dirEnt->d_name, ".") == 0 || strcmp(dirEnt->d_name, "..") == 0) {
            provera_greske(stat(novaPutanja, &fInfo) != -1, "");
            if(S_ISREG(fInfo.st_mode)) {
                if((int)ceil(difftime(vreme_sad, fInfo.st_mtime)/(double)SEKUNDE_U_DANU) <= DANI_MODIFIKACIJE) {
                    char* s = basename(putanja);
                    fprintf(stdout, "%s\n", s);
                }
            }
            free(novaPutanja);
            continue;
        }
        obidjiDir(novaPutanja, vreme_sad);
        free(novaPutanja);
    }

    provera_greske(closedir(dir) != -1, "");
}

int main(int argc, char** argv) {

    provera_greske(argc == 2, "");

    struct stat fInfo;
    provera_greske(stat(argv[1], &fInfo) != -1, "");
    provera_greske(S_ISDIR(fInfo.st_mode), "");

    time_t vreme_sad = time(NULL);
    provera_greske(vreme_sad != (time_t)-1, "");
    obidjiDir(argv[1], vreme_sad);

    exit(EXIT_SUCCESS);
}