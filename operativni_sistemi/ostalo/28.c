#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>

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

    provera_greske(argc == 4, "");

    struct stat fInfo;
    provera_greske(stat(argv[1], &fInfo) != -1, "");
    provera_greske(S_ISREG(fInfo.st_mode), "");

    off_t p = atoi(argv[2]);
    int n = atoi(argv[3]);

    int fd = open(argv[1], O_RDWR);
    provera_greske(fd != -1, "");

    char* bafer = (char*)malloc(n*sizeof(char));
    provera_greske(bafer != NULL, "");

    provera_greske(pread(fd, bafer, n, p) != -1, "");

    char* bafertmp = (char*)malloc(n*sizeof(char));
    provera_greske(bafertmp != NULL, "");
    for(int i = 0, j = n-1; i < n; i++, j--) {
        bafertmp[i] = bafer[j];
    }

    provera_greske(pwrite(fd, bafertmp, n, p) != -1, "");

    close(fd);
    free(bafer);
    free(bafertmp);
    exit(EXIT_SUCCESS);
}