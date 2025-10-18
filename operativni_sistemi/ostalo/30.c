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

    struct stat fInfo1;
    provera_greske(stat(argv[1], &fInfo1) != -1, "");

    struct stat fInfo2;
    provera_greske(stat(argv[2], &fInfo2) != -1, "");

    int fd = open(argv[3], O_RDONLY | O_CREAT);
    provera_greske(fd != -1, "");
    close(fd);

    mode_t mod = fInfo1.st_mode & fInfo2.st_mode;
    provera_greske(chmod(argv[3], mod) != -1, "");

    exit(EXIT_SUCCESS);
}