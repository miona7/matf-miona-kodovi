#define _XOPEN_SOURCE (700)
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

    int fd = open(argv[1], O_RDONLY);
    provera_greske(fd != -1, "");

    int a = strtol(argv[2], NULL, 10);
    int b = strtol(argv[3], NULL, 10);

    provera_greske(lseek(fd, a, SEEK_SET) != (off_t)-1, "");
    
    struct flock katanac;
    katanac.l_start = a;
    katanac.l_len = b;
    katanac.l_type = F_WRLCK;
    katanac.l_whence = SEEK_SET;

    provera_greske(fcntl(fd, F_GETLK, &katanac) != -1, "");
    if(katanac.l_type == F_UNLCK) {
        fprintf(stdout, "unlocked\n");
    } else if(katanac.l_type == F_RDLCK) {
        fprintf(stdout, "shared lock\n");
    } else if(katanac.l_type == F_WRLCK) {
        fprintf(stdout, "exclusive lock\n");
    }

    close(fd);
    exit(EXIT_SUCCESS);
}