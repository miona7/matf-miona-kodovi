#define _XOPEN_SOURCE (700)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

#define MAX (256)

int main(int argc, char** argv) {
    
    provera_greske(argc == 2, "");

    struct stat fInfo;
    provera_greske(stat(argv[1], &fInfo) != -1, "");
    provera_greske(S_ISREG(fInfo.st_mode), "");

    int fd = open(argv[1], O_RDWR);
    provera_greske(fd != -1, "");

    FILE* ulaz = fdopen(fd, "r+");
    provera_greske(ulaz != NULL, "");

    char rec[MAX]; int brojac = 0;
    while(fscanf(ulaz, "%s", rec) == 1) {
        char* endptr = NULL;
        int x = strtol(rec, &endptr, 10);

        if(*rec != '\0' && *endptr == '\0') {
            struct flock katanac;
            katanac.l_type = F_WRLCK;
            katanac.l_start = ftell(ulaz);
            katanac.l_len = strlen(rec);
            katanac.l_whence = SEEK_SET;

            int rez = fcntl(fd, F_GETLK, &katanac);
            if(rez == -1) {
                if(errno != EACCES && errno != EAGAIN) {
                    provera_greske(0, "");
                }
            } else {
                int n = strlen(rec);
                provera_greske(fseek(ulaz, -n, SEEK_CUR) != -1, "");
                for(int i = 0; i < n; i++) {
                    fprintf(ulaz, "#");
                }
                brojac += n;
                katanac.l_type = F_UNLCK;
                provera_greske(fcntl(fd, F_SETLK, &katanac) != -1, "");
            }
        }
    }

    fprintf(stdout, "%d\n", brojac);
    fclose(ulaz);
    exit(EXIT_SUCCESS);
}