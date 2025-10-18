#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>

#include <stdbool.h>

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

bool osIsPublicFile(const char* fpath) {

    struct stat fInfo;
    provera_greske(stat(fpath, &fInfo) != -1, "Nepostojeci fajl");
    
    provera_greske(S_ISREG(fInfo.st_mode), "Pogresan tip fajla");

    if((fInfo.st_mode & S_IROTH) && (fInfo.st_mode & S_IWOTH)) {
        return true;
    }
    else {
        return false;
    }
}

int main(int argc, char** argv) {

    provera_greske(argc == 2, "");

    if(osIsPublicFile(argv[1])) {
        fprintf(stdout, "true\n");
    }
    else {
        fprintf(stdout, "false\n");
    }

    exit(EXIT_SUCCESS);
}