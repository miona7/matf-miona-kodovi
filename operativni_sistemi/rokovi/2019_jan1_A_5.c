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

#define MAX (256)

int main(int argc, char** argv) {
    
    provera_greske(argc == 3, "");
    
    int fd = open(argv[1], O_RDWR);
    provera_greske(fd != -1, "");

    FILE* ulaz = fdopen(fd, "r+");
    provera_greske(ulaz != NULL, "");

    char bafer[MAX];
    while(fscanf(ulaz, "%s", bafer) == 1) {
        if(strcmp(bafer, argv[2]) == 0) {
            struct flock katanac;
            katanac.l_type = F_WRLCK;
            katanac.l_whence = SEEK_SET;
            katanac.l_start = ftell(ulaz);
            katanac.l_len = -strlen(bafer);

            provera_greske(fcntl(fd, F_GETLK, &katanac) != -1, "");

            switch(katanac.l_type) {
                case F_WRLCK:
                    fprintf(stdout, "%d w\n", ftell(ulaz) - strlen(bafer));
                    break;
                case F_RDLCK:
                    fprintf(stdout, "%d r\n", ftell(ulaz) - strlen(bafer));
                    break;
            }
        }
    }

    fclose(ulaz);
    exit(EXIT_SUCCESS);
}