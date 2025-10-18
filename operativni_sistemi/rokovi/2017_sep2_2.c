#define _XOPEN_SOURCE (700)
#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#define provera_greske(uslov, poruka) \
    do { \
        if(!(uslov)) { \
            fprintf(stderr, "%s\n", poruka); \
            exit(EXIT_FAILURE); \
        } \
    } while(0)

#define MAX (257)

int main(int argc, char** argv) {
    
    provera_greske(argc == 2, "");

    struct stat fInfo;
    provera_greske(stat(argv[1], &fInfo) != -1, "");

    int fd = open(argv[1], O_RDWR);
    provera_greske(fd != -1, "");
    
    FILE* ulaz = fdopen(fd, "r+");
    provera_greske(ulaz != NULL, "");

    char rec[MAX];
    while(fscanf(ulaz, "%s", rec) == 1) {
        //int x = strtol(rec, NULL, 10);
        int x = atoi(rec);
        if(x >= 1000 && x <= 9999) {
            struct flock katanac;
            katanac.l_type = F_WRLCK;
            katanac.l_whence = SEEK_SET;
            katanac.l_start = ftell(ulaz);
            katanac.l_len = -4;

            int rez = fcntl(fd, F_SETLK, &katanac);
            if(rez == -1) {
                if(errno != EACCES && errno != EAGAIN) {
                    provera_greske(0, "");
                }
            } else {
                provera_greske(fseek(ulaz, -4, SEEK_CUR) != -1, "");
                fprintf(ulaz, "####");

                katanac.l_type = F_UNLCK;
                provera_greske(fcntl(fd, F_SETLK, &katanac) != -1, "");
            }
        }
    }

    fclose(ulaz);
    exit(EXIT_SUCCESS);
}