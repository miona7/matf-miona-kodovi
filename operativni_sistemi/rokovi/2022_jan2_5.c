#define _XOPEN_SOURCE (700)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#define provera_greske(uslov, poruka) \
    do { \
        if(!(uslov)) { \
            fprintf(stderr, "%s\n", poruka); \
            exit(EXIT_FAILURE); \
        } \
    } while(0)

#define MAX (256)

bool ispunjava_uslove(char* rec) {
    for(int i = 0; rec[i] != '\0'; i++) {
        if(islower(rec[i]) || isdigit(rec[i]) || !isalpha(rec[i])) {
            return false;
        }
    }
    return true;
}

int main(int argc, char** argv) {

    provera_greske(argc == 2, "");

    int fd = open(argv[1], O_RDWR);
    provera_greske(fd != -1, "");

    FILE* ulaz = fdopen(fd, "r+");
    provera_greske(ulaz != NULL, "");

    int brojac = 0;
    char rec[MAX];
    while(fscanf(ulaz, "%s", rec) == 1) {
        if(ispunjava_uslove(rec)) {
            int m = strlen(rec);
            struct flock katanac;
            katanac.l_type = F_WRLCK;
            katanac.l_len = -m;
            katanac.l_start = ftell(ulaz);
            katanac.l_whence = SEEK_SET;

            int rez = fcntl(fd, F_SETLK, &katanac);
            if(rez == -1) {
                if(errno != EACCES && errno != EAGAIN) {
                    provera_greske(0, "");
                }
            } else {
                provera_greske(fseek(ulaz, -m, SEEK_CUR) != -1, "");
                
                for(int i = 0; rec[i] != '\0'; i++) {
                    rec[i] = '#';
                }
                fprintf(ulaz, "%s", rec);
                brojac += m;

                katanac.l_type = F_UNLCK;
                provera_greske(fcntl(fd, F_SETLK, &katanac) != -1, "");
            }
        }
    }

    fprintf(stdout, "%d\n", brojac);

    fclose(ulaz);
    exit(EXIT_SUCCESS);
}
