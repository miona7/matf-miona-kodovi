#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#define provera_greske(uslov, poruka) \
    do { \
        if(!(uslov)) { \
            fprintf(stderr, "%s\n", poruka); \
            exit(EXIT_FAILURE); \
        } \
    } while(0)

int main(int argc, char** argv) {

    provera_greske(argc == 5, "");

    struct stat fInfo;
    provera_greske(stat(argv[1], &fInfo) != -1, "");
    provera_greske(S_ISREG(fInfo.st_mode), "");

    off_t a = atoi(argv[2]);
    off_t b = atoi(argv[3]);
    int n = atoi(argv[4]);

    int fd = open(argv[1], O_RDWR);
    provera_greske(fd != -1, "");
    
    char* bafer1 = (char*)malloc(n*sizeof(char));
    provera_greske(bafer1 != NULL, "");
    char* bafer2 = (char*)malloc(n*sizeof(char));
    provera_greske(bafer2 != NULL, "");

    provera_greske(pread(fd, bafer1, n, a) != -1, "");
    provera_greske(pread(fd, bafer2, n, b) != -1, "");

    provera_greske(pwrite(fd, bafer2, n, a) != -1, "");
    provera_greske(pwrite(fd, bafer1, n, b) != -1, "");

    close(fd);
    free(bafer1);
    free(bafer2);
    exit(EXIT_SUCCESS);
}