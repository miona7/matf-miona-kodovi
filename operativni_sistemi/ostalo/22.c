#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

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
    mode_t mod = strtol(argv[3], NULL, 8);

    if(strcmp(argv[1], "-f") == 0) {
        int fd = open(argv[2], O_CREAT, mod);
        provera_greske(fd != -1, "");
        provera_greske(chmod(argv[2], mod) != -1, "");
        close(fd);
    } else if(strcmp(argv[1], "-d") == 0) {
        int md = mkdir(argv[2], mod);
        if(errno == EEXIST) {
            provera_greske(chmod(argv[2], mod) != -1, "");
        } else if(md != -1) {
            provera_greske(chmod(argv[2], mod) != -1, "");
        } else {
            provera_greske(0, "");
        }
    } else {
        provera_greske(0, "");
    }

    exit(EXIT_SUCCESS);
}