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

#define MAX (1024)
#define PRAVA (0644)

int main(int argc, char** argv) {
    
    provera_greske(argc == 3, "");

    int fd_ulaz = open(argv[1], O_RDONLY);
    provera_greske(fd_ulaz != -1, "");

    int fd_izlaz = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, PRAVA);
    provera_greske(fd_izlaz != -1, "");

    char bafer[MAX];
    int procitano = 0;
    while((procitano = read(fd_ulaz, bafer, MAX)) > 0) {
        provera_greske(write(fd_izlaz, bafer, procitano) != -1, "");
    }
    provera_greske(procitano != -1, "");
    
    close(fd_ulaz);
    close(fd_izlaz);

    struct stat fInfo;
    provera_greske(stat(argv[1], &fInfo) != -1, "");
    provera_greske(chmod(argv[2], fInfo.st_mode) != -1, "");

    provera_greske(unlink(argv[1]) != -1, "");

    exit(EXIT_SUCCESS);
}