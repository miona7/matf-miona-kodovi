#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define provera_greske(uslov, poruka) \
    do { \
        if(!(uslov)) { \
            fprintf(stderr, "%s\n", poruka); \
            exit(EXIT_FAILURE); \
        } \
    } while(0)

int main(int argc, char** argv) {

    provera_greske(argc == 3, "");

    struct stat fInfo1;
    provera_greske(stat(argv[1], &fInfo1) != -1, "");

    struct stat fInfo2;
    provera_greske(stat(argv[2], &fInfo2) != -1, "");

    char* fajl1 = NULL;
    char* ime = strrchr(argv[1], '/');

    if(ime != NULL) {
        fajl1 = (char*)malloc(sizeof(ime+1));
        strcpy(fajl1, ime+1);
    }
    else {
        fajl1 = (char*)malloc(sizeof(argv[1]));
        strcpy(fajl1, argv[1]);
    }

    char* fajl2 = NULL;
    char* ime2 = strrchr(argv[2], '/');

    if(ime2 != NULL) {
        fajl2 = (char*)malloc(sizeof(ime2+1));
        strcpy(fajl2, ime2+1);
    }
    else {
        fajl2 = (char*)malloc(sizeof(argv[2]));
        strcpy(fajl2, argv[2]);
    }

    if(fInfo1.st_mtime > fInfo2.st_mtime) {
        fprintf(stdout, "%s\n", fajl1);
    }
    else {
        fprintf(stdout, "%s\n", fajl2);
    }

    exit(EXIT_SUCCESS);
}