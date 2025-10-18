#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>

#define provera_greske(uslov, poruka) \
    do { \
        if(!(uslov)) { \
            fprintf(stderr, "%s\n", poruka); \
            exit(EXIT_FAILURE); \
        } \
    } while(0)

char* ext = NULL;

void obidji_direktorijum(char* fPath, int* brojac) {
    
    struct stat fInfo;
    provera_greske(lstat(fPath, &fInfo) != -1, "");

    if(!S_ISDIR(fInfo.st_mode)) {
        char* ekstenzija = strrchr(fPath, '.');
        if(ekstenzija != NULL && strcmp(ekstenzija, ext) == 0) {
            *brojac += 1;
        }
        return;
    }

    DIR* dir = opendir(fPath);
    provera_greske(dir != NULL, "");

    struct dirent* dirEnt = NULL;
    while((dirEnt = readdir(dir)) != NULL) {
        int n = strlen(fPath) + strlen(dirEnt->d_name) + 2;
        char* novaPutanja = (char*)malloc(n*sizeof(char));
        provera_greske(novaPutanja != NULL, "");
        sprintf(novaPutanja, "%s/%s", fPath, dirEnt->d_name);

        if(strcmp(dirEnt->d_name, ".") == 0 || strcmp(dirEnt->d_name, "..") == 0) {
            
            struct stat fInfo;
            provera_greske(stat(novaPutanja, &fInfo) != -1, "");

            char* ekstenzija = strrchr(novaPutanja, '.');
            if(ekstenzija != NULL && strcmp(ekstenzija, ext) == 0) {
                *brojac += 1;
            }
            free(novaPutanja);
            continue;
        }
        obidji_direktorijum(novaPutanja, brojac);
        free(novaPutanja);
    }

    provera_greske(closedir(dir) != -1, "");
}

int main(int argc, char** argv) {

    provera_greske(argc == 3, "");

    struct stat fInfo;
    provera_greske(stat(argv[1], &fInfo) != -1, "");
    provera_greske(S_ISDIR(fInfo.st_mode), "");

    ext = argv[2];
    int brojac = 0;
    obidji_direktorijum(argv[1], &brojac);

    fprintf(stdout, "%d\n", brojac);

    exit(EXIT_SUCCESS);
}