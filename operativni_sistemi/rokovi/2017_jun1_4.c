#define _XOPEN_SOURCE (700)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

#define MAX (257)

bool is_num(char* buffer) {

    char* endptr = NULL;
    strtol(buffer, &endptr, 10);

    if(*buffer != '\0' && *endptr == '\0') {
        return true;
    }
    return false;
}

int main(int argc, char** argv) {
    
    provera_greske(argc == 2, "");

    struct stat fInfo;
    provera_greske(stat(argv[1], &fInfo) != -1, "");

    int fd = open(argv[1], O_RDONLY);
    provera_greske(fd != -1, "");

    FILE* ulaz = fdopen(fd, "r");
    provera_greske(ulaz != NULL, "");

    char rec[MAX]; int brojac = 0;
    while(fscanf(ulaz, "%s", rec) == 1) {
        if(is_num(rec)) {
            struct flock katanac;
            katanac.l_type = F_RDLCK;
            katanac.l_start = ftell(ulaz);
            katanac.l_whence = SEEK_SET;
            katanac.l_len = -strlen(rec);

            int rez = fcntl(fd, F_SETLK, &katanac);
            if(rez == -1) {
                if(errno != EACCES && errno != EAGAIN) {
                    provera_greske(0, "");
                }
            } else {
                brojac++;
            }
        }
    }
    fprintf(stdout, "%d\n", brojac);

    fclose(ulaz);
    exit(EXIT_SUCCESS);
}