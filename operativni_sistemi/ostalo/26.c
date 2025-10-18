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
    int a = atoi(argv[2]); int b = atoi(argv[3]);

    int fd = open(argv[1], O_RDONLY);
    provera_greske(fd != -1, "");

    int preostalo = b;
    char bafer[MAX];
    while(preostalo > 0) {
        provera_greske(lseek(fd, a, SEEK_SET) != (off_t)-1, "");
        int procitano = read(fd, bafer, preostalo < MAX ? preostalo : MAX);
        provera_greske(procitano != -1, "");
        provera_greske(write(STDOUT_FILENO, bafer, procitano) != -1, "");
        preostalo -= procitano;
    }

    close(fd);
    exit(EXIT_SUCCESS);
}