#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#define MAX (1024)

#define provera_greske(uslov, poruka) \
    do { \
        if(!(uslov)) { \
            fprintf(stderr, "%s\n", poruka); \
            exit(EXIT_FAILURE); \
        } \
    } while(0)

void osMoveFile(const char* srcPath, const char* destPath) {
    //provera_greske(strcmp(srcPath, destPath) != 0, "");

    struct stat fInfo;
    provera_greske(stat(srcPath, &fInfo) != -1, "");

    int fdSrc = open(srcPath, O_RDONLY);
    provera_greske(fdSrc != -1, "");

    int fdDest = open(destPath, O_WRONLY | O_CREAT | O_TRUNC);
    provera_greske(fdDest != -1, "");

    int procitano = 0;
    char bafer[MAX];
    while((procitano = read(fdSrc, bafer, MAX)) > 0) {
        provera_greske(write(fdDest, bafer, procitano) != -1, "");
    }
    provera_greske(procitano != -1, "");

    close(fdSrc);
    close(fdDest);

    provera_greske(unlink(srcPath) != -1, "");
    provera_greske(chmod(destPath, fInfo.st_mode) != -1, "");
}

int main(int argc, char** argv) {

    provera_greske(argc == 3, "");

    osMoveFile(argv[1], argv[2]);

    exit(EXIT_SUCCESS);
}