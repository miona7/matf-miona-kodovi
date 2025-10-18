#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>

#define provera_greske(uslov, poruka) \
    do { \
        if(!(uslov)) { \
            fprintf(stderr, "%s\n", poruka); \
            exit(EXIT_FAILURE); \
        } \
    } while(0)

void obidji_direktorijum(char* fPath, long long int* minVelicina, long long int* maxVelicina) {

    struct stat fInfo;
    provera_greske(lstat(fPath, &fInfo) != -1, "");

    if(!(S_ISDIR(fInfo.st_mode))) {
        if(fInfo.st_size > *maxVelicina) {
            *maxVelicina = fInfo.st_size;
        }
        if(fInfo.st_size < *minVelicina) {
            *minVelicina = fInfo.st_size;
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

            if(fInfo.st_size > *maxVelicina) {
                *maxVelicina = fInfo.st_size;
            }
            if(fInfo.st_size < *minVelicina) {
                *minVelicina = fInfo.st_size;
            }
                
            free(novaPutanja);
            continue;
        }

        obidji_direktorijum(novaPutanja, minVelicina, maxVelicina);
        free(novaPutanja);
    }
    provera_greske(closedir(dir) != -1, "");
}

int main(int argc, char** argv) {

    provera_greske(argc == 2, "");

    struct stat fInfo;
    provera_greske(stat(argv[1], &fInfo) != -1, "");

    provera_greske(S_ISDIR(fInfo.st_mode), "");

    long long int minVelicina = INT_MAX;
    long long int maxVelicina = INT_MIN;

    obidji_direktorijum(argv[1], &minVelicina, &maxVelicina);
    fprintf(stdout, "%lld\n", maxVelicina-minVelicina);

    exit(EXIT_SUCCESS);
}