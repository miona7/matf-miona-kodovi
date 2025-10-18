#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <libgen.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>

#define MAX 5

#define provera_greske(uslov, poruka) \
    do { \
        if(!(uslov)) { \
            fprintf(stderr, "%s\n", poruka); \
            exit(EXIT_FAILURE); \
        } \
    } while(0)

bool treba_ispisati_fajl(const char* putanja) {
    char* ime = basename(putanja);
    char ime_dir[MAX] = {ime[0], ime[1], ime[2], ime[3], '\0'};

    return strcmp(ime_dir, "dir_") == 0;
}
 
void obidji_direktorijum(const char* fPath, bool treba_ispisati) {

    DIR* dir = opendir(fPath);
    provera_greske(dir != NULL, "");

    provera_greske(chdir(fPath) != -1, "");

    struct dirent* dirEnt = NULL;
    while((dirEnt = readdir(dir)) != NULL) {
        struct stat f_info;
        provera_greske(lstat(dirEnt->d_name, &f_info) != -1, "");

        if(S_ISREG(f_info.st_mode)) {
            if(treba_ispisati) {
                fprintf(stdout, "%s\n", dirEnt->d_name);
            } 
        } else if(S_ISDIR(f_info.st_mode)) {
            if(strcmp(dirEnt->d_name, ".") != 0 && strcmp(dirEnt->d_name, "..") != 0) {
                obidji_direktorijum(dirEnt->d_name, treba_ispisati_fajl(dirEnt->d_name) || treba_ispisati);
            }
        }
    }
    provera_greske(closedir(dir) != -1, "");
    provera_greske(chdir("..") != -1, "");
}

int main(int argc, char** argv) {

    provera_greske(argc == 2, "");

    struct stat fInfo;
    provera_greske(stat(argv[1], &fInfo) != -1, "");
    provera_greske(S_ISDIR(fInfo.st_mode), "");

    obidji_direktorijum(argv[1], treba_ispisati_fajl(argv[1]));

    exit(EXIT_SUCCESS);
} 