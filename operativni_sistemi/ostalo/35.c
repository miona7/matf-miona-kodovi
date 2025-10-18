#include <stdio.h>
#include <stdlib.h>

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

    provera_greske(argc == 4, "");

    struct stat fInfo;
    provera_greske(stat(argv[1], &fInfo) != -1, "");
    provera_greske(S_ISREG(fInfo.st_mode), "");

    int pozicija = atoi(argv[2]);
    int duzina = atoi(argv[3]);

    int fd = open(argv[1], O_RDONLY);
    provera_greske(fd != -1, "");
    provera_greske(lseek(fd, pozicija, SEEK_SET) != (off_t)-1, "");

    int procitano = 0;
    char bafer[MAX];
    while(duzina > 0) {
        procitano = read(fd, bafer, duzina);
        provera_greske(procitano != -1, "");
        provera_greske(write(STDOUT_FILENO, bafer, procitano) != -1, "");
        duzina -= procitano;
    }    
    fprintf(stdout, "\n");
    close(fd);
    exit(EXIT_SUCCESS);
}