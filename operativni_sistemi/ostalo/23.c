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

int main(int argc, char** argv) {

    provera_greske(argc == 3, "");

    if(strcmp(argv[1], "-r") == 0) {
        int procitano = 0;
        char bafer[MAX];
        int fd = open(argv[2], O_RDONLY);
        while((procitano = read(fd, bafer, MAX)) > 0) {
            provera_greske(write(STDOUT_FILENO, bafer, procitano) != -1, "");
        }
        provera_greske(procitano != -1, "");
        close(fd);
    } else if(strcmp(argv[1], "-w") == 0) {
        int procitano = 0;
        char bafer[MAX];
        int fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC);
        while((procitano = read(STDIN_FILENO, bafer, MAX)) > 0) {
            provera_greske(write(fd, bafer, procitano) != -1, "");
        }
        provera_greske(procitano != -1, "");
        close(fd);
    } else if(strcmp(argv[1], "-a") == 0) {
        int procitano = 0;
        char bafer[MAX];
        int fd = open(argv[2], O_WRONLY | O_CREAT | O_APPEND);
        while((procitano = read(STDIN_FILENO, bafer, MAX)) > 0) {
            provera_greske(write(fd, bafer, procitano) != -1, "");
        }
        provera_greske(procitano != -1, "");
        close(fd);
    } else {
        provera_greske(0, "");
    }

    exit(EXIT_SUCCESS);
}